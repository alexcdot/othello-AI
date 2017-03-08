#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
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
    if (testingMinimax)
    {
        std::cerr << "testing minimax" << std::endl;
        board.doMove(opponentsMove, otherSide);
        Move *bestMove = MinimaxHelper(); 
        board.doMove(bestMove, side);
           
        return bestMove;
    }
    else
    {
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
                    score = heuristic.score(copy, side);
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
}

/* MinimaxHelper is the first function call for minimax. Unlike Maximize or
 * Minimze, it returns the best move rather than the best score. Otherwise, it
 * is basically a Maximize call. If there are no possible moves, it will return
 * a nullptr.
 *
*/

Move *Player::MinimaxHelper()
{
    if (!board.hasMoves(side))
    {
        return nullptr;
    }
    
    int score;
    int depth = 0;
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int bestScore = INT_MIN;   
    Board *copy = nullptr;      // copy of the board after making the move
    Move move(-1, -1);          // move being considered
    Move bestMove(-1, -1);      

    // iterate through the positions in the board to see if they are moves

    for (int i = 0; i < 8; i++) {
        move.y = i;
        for (int j = 0; j < 8; j++) {
            move.x = j;
            
            if (board.checkMove(&move, side)) {
                
                std::cerr << move.getX() << " " << move.getY() << std::endl;
                
                // create a copy of the board where you do the move
                
                copy = board.copy();
                copy->doMove(&move, side);
                
                // if the depth of recursion is too great, or there are no
                // possible moves for either side, just return board score
                
                if (depth > 1 || (!copy->hasMoves(side) 
                && !copy->hasMoves(otherSide))) {
                    score = heuristic.score(copy, side);
                }
                
                // if the opponent doesn't have moves, skip their turn
                
                else if (!copy->hasMoves(otherSide)) {
                    score = Maximize(copy, depth + 1, alpha, beta);
                }
                
                // otherwise, allow the opponent to make their turn
                
                else {
                    score = Minimize(copy, depth + 1, alpha, beta);
                }
                
                delete copy;
                copy = nullptr;
                
                // keep track of the best score, and update alpha and beta
                
                if (score > bestScore) {
                    bestScore = score;
                    bestMove.x = move.x;
                    bestMove.y = move.y;
                }
                if (score > alpha) {
                    alpha = score;
                }
                if (alpha >= beta) {
                    return new Move (bestMove.getX(), bestMove.getY());
                }
            }
        }
    } 
    
    return new Move (bestMove.getX(), bestMove.getY());
}

/* Maximize tries to find the best move with a minimizing player. See comments
 * inline in MinimaxHelper
 * Maximize returns the maximum possible score.
 *
*/

int Player::Maximize(Board *board, int depth, int alpha, int beta)
{
    int score;
    int bestScore = INT_MIN;
    Move move(-1, -1);
    Board *copy = nullptr;

    for (int i = 0; i < 8; i++) {
        move.y = i;
        for (int j = 0; j < 8; j++) {
            move.x = j;
            if (board->checkMove(&move, side)) {
            
                std::cerr << move.getX() << " " << move.getY() << std::endl;

                copy = board->copy();
                copy->doMove(&move, side);
                
                if (depth > 1 || (!copy->hasMoves(side) 
                && !copy->hasMoves(otherSide))) {
                    score = heuristic.score(copy, side);
                }
                else if (!copy->hasMoves(otherSide)) {
                    score = Maximize(copy, depth + 1, alpha, beta);
                }
                else {
                    score = Minimize(copy, depth + 1, alpha, beta);
                }
                
                delete copy;
                copy = nullptr;
                
                if (score > bestScore) {
                    bestScore = score;
                }
                if (score > alpha) {
                    alpha = score;
                }
                if (alpha >= beta) {
                    return alpha;
                }
            }
        }
    } 
    std::cerr << bestScore << std::endl;
    return bestScore; 
}

/* Minimize tries to find the best move against a maximizing player. 
 * Minimize returns the minimum possible score.
*/

int Player::Minimize(Board *board, int depth, int alpha, int beta)
{
    int score;
    int bestScore = INT_MAX;
    Move move(-1, -1);
    Board *copy = nullptr;
    
    for (int i = 0; i < 8; i++) {
        move.y = i;
        for (int j = 0; j < 8; j++) {
            move.x = j;
            if (board->checkMove(&move, otherSide)) {

                std::cerr << move.getX() << " " << move.getY() << std::endl;

                copy = board->copy();
                copy->doMove(&move, otherSide);
                
                if (depth > 1 || (!copy->hasMoves(side) 
                && !copy->hasMoves(otherSide))) {
                    score = heuristic.score(copy, side);
                }
                
                else if (!copy->hasMoves(side)) {
                    score = Minimize(copy, depth + 1, alpha, beta);
                }
                else {
                    score = Maximize(copy, depth + 1, alpha, beta);
                }
                
                delete copy;
                copy = nullptr;
                
                if (score < bestScore) {
                    bestScore = score;
                }
                if (score < beta) {
                    beta = score;
                }
                if (alpha >= beta) {
                    return beta;
                }
            }
        }
    }
    std::cerr << bestScore << std::endl;
    return bestScore;
}
