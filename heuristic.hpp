#ifndef __HEURISTIC_H__
#define __HEURISTIC_H__

#include "common.hpp"
#include "board.hpp"

class Heuristic {
public:
    Heuristic(Side s);

    int score(Board *board);

protected:
    Side side;
    Side otherSide;
};

#endif
