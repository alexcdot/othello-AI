#include <climits>
#include <iostream>

#include "heuristic.hpp"

int Heuristic::score(Board *board, Side side) {
    Side otherSide = (side == BLACK) ? WHITE : BLACK;
    // The simple scheme of +1 for our color, -1 for their color
    int basicCount = board->count(side) - board->count(otherSide);

    // Special value is placed on pieces that can never be flipped.
    // This is always the case for corners, but a piece adjacent to a piece in a
    // corner will also satisfy this, and so on.
    bool fixed[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fixed[i][j] = false;
        }
    }
    int fixedCount = 0;
    int corners = 0;;
    int xsquares = 0;;
    int csquares = 0;;
    for (int dx = 1; dx >= -1; dx -= 2) {
        for (int dy = 1; dy >= -1; dy -= 2) {
            int x = (dx == 1) ? 0 : 7;
            int y = (dy == 1) ? 0 : 7;
            if (board->occupied(x, y)) {
                Side source = board->get(BLACK, x, y) ? BLACK : WHITE;
                int thisCount = 0;
                bool going = true;
                for (int i = 0; going; i++) {
                    going = false;
                    for (int j = 0; j <= i; j++) {
                        int xj = x + j * dx;
                        int yj = y + (i - j) * dy;
                        if (xj < 0 || xj > 7 || yj < 0 || yj > 7) {
                            continue;
                        }
                        if (board->get(source, xj, yj) &&
                        (!board->onBoard(xj - 1, yj) ||
                          board->get(source, xj - 1, yj)) &&
                        (!board->onBoard(xj, yj - 1) ||
                          board->get(source, xj, yj - 1))) {
                            if (!fixed[xj][yj]) { // Avoid double-counting
                                thisCount++;
                                fixed[xj][yj] = true;
                                going = true;
                            }
                        }
                    }
                }
                if (source == side) {
                    corners++;
                } else {
                    // Fixed points of opponent color reduce score
                    thisCount *= -1;
                    corners--;
                }
                fixedCount += thisCount;
            } else {
                // Corner is open, so it would be bad to give access to it
                if (board->occupied(x + dx, y + dy)) {
                    xsquares += (board->get(side, x + dx, y + dy)) ? 1 : -1;
                }
                if (board->occupied(x + dx, y)) {
                    csquares += (board->get(side, x + dx, y)) ? 1 : -1;
                }
                if (board->occupied(x, y + dy)) {
                    csquares += (board->get(side, x, y + dy)) ? 1 : -1;
                }
            }
        }
    }

    int ourMoves = board->countMoves(side);
    int oppMoves = board->countMoves(otherSide);
    if (ourMoves == 0 && oppMoves == 0) {
        // Game over! Approximately infinitely good for the winner.
        // Might as well distinguish by margin of victory
        // Never actually return INT_MAX or INT_MIN so as not to be equal to the
        // dummy value used in finding the min / max of a set
        int result;
        if (basicCount > 0) {
            // Win
            result = INT_MAX - 100;
            result += basicCount;
        } else if (basicCount < 0) {
            // Loss
            int result = INT_MIN + 100;
            result += basicCount;
        } else {
            // Tie
            // Less desirable than continued gameplay, but much better than loss
            result = INT_MIN / 2;
        }
        return result;
    }
    int moves = ourMoves - oppMoves;

    int discWeight;
    int moveWeight;

    switch(board->countEmpty() / 10) {
      case 6:
        // Starting configuration: doesn't matter, score will be zero anyway
        discWeight = 0;
        moveWeight = 0;
        break;
      case 5:
      case 4:
        // Early game. Moves much more important than unstable discs.
        discWeight = 1;
        moveWeight = 15;
        break;
      case 3:
        // Early middle game. Moves still of dominating importance.
        discWeight = 5;
        moveWeight = 15;
        break;
      case 2:
        // Late game. Discs becoming more important.
        discWeight = 15;
        moveWeight = 15;
        break;
      case 1:
        // Near endgame. Time to focus on securing discs.
        discWeight = 15;
        moveWeight = 5;
        break;
      case 0:
        // Endgame. Discs now quite important.
        discWeight = 15;
        moveWeight = 1;
        break;
      default:
        // Something has gone terribly wrong
        cerr << "Nonsensical number of empty squares: " << board->countEmpty();
        cerr << endl;
        break;
    }

    int fixedWeight = 50;
    int cornerWeight = 150; // Note that corners get counted as corners and fixed
    int xsquareWeight = -100;
    int csquareWeight = -70;

    int result = 0;
    result += basicCount * discWeight;
    result += moves * moveWeight;
    result += fixedCount * fixedWeight;
    result += corners * cornerWeight;
    result += xsquares * xsquareWeight;
    result += csquares * csquareWeight;
    return result;
}
