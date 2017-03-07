#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <climits>
#include "common.hpp"
#include "board.hpp"
#include "heuristic.hpp"

using namespace std;

class Player {
public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *MinimaxHelper();
    
    int Maximize(Board *board, int depth, int alpha, int beta);
    int Minimize(Board *board, int depth, int alpha, int beta);
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    void setBoard(char data[]) { board.setBoard(data); }

private:
    Side side;
    Side otherSide;
    Board board;
    Heuristic heuristic;
};

#endif
