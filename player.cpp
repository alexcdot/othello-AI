#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) : heuristic(side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    this->side = side;
    // Easier than recomputing it each time
    otherSide = (side == BLACK) ? WHITE : BLACK;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    board.doMove(opponentsMove, otherSide);
    Move move(-1, -1);
    Move bestMove(-1, -1);
    Board *copy = nullptr;
    int score = INT_MIN;
    int bestScore = INT_MIN;
    for (int i = 0; i < 8; i++) {
        move.y = i;
        for (int j = 0; j < 8; j++) {
            move.x = j;
            if (board.checkMove(&move, side)) {
                copy = board.copy();
                copy->doMove(&move, side);
                score = heuristic.score(copy);
                delete copy;
                copy = nullptr;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove.x = move.x;
                    bestMove.y = move.y;
                }
            }
        }
    }
    if (bestMove.x != -1) {
        board.doMove(&bestMove, side);
        return new Move(bestMove.x, bestMove.y);
    }
    return nullptr;
}
