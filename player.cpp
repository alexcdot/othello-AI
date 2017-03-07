#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) : heuristic(side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;

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
        std::cerr << "side (white is 0) " << side << std::endl;
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
}

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
    Board *copy = nullptr;
    Move move(-1, -1);
    Move bestMove(-1, -1);

    for (int i = 0; i < 8; i++) {
        move.y = i;
        for (int j = 0; j < 8; j++) {
            move.x = j;
            
            if (board.checkMove(&move, side)) {
                
                std::cerr << move.getX() << " " << move.getY() << std::endl;
                
                copy = board.copy();
                copy->doMove(&move, side);
                
                if (depth > 1 || (!copy->hasMoves(side) 
                && !copy->hasMoves(otherSide))) {
                    score = copy->count(side) - copy->count(otherSide);
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
                    bestMove.x = move.x;
                    bestMove.y = move.y;
                }
                if (score > alpha) {
                    alpha = score;
                }
                if (alpha >= beta) {
                    Move *returnMove = new Move (bestMove.getX(), 
                    bestMove.getY());
                    return returnMove;
                }
            }
        }
    } 
    Move *returnMove = new Move (bestMove.getX(), bestMove.getY());
    
    return returnMove;
}

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
                    score = copy->count(side) - copy->count(otherSide);
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
                    score = copy->count(side) - copy->count(otherSide);
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
