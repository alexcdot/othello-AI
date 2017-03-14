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

    int fixedWeight = 5;
    int cornerWeight = 15; // Note that corners get counted as corners and fixed
    int xsquareWeight = -10;
    int csquareWeight = -5;

    int result = 0;
    result += basicCount;
    result += fixedCount * fixedWeight;
    result += corners * cornerWeight;
    result += xsquares * xsquareWeight;
    result += csquares * csquareWeight;
    return result;
}
