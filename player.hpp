#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
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

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
    Side side;
    Side otherSide;
    Board board;
    Heuristic heuristic;
};

#endif
