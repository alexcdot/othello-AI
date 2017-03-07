#ifndef __HEURISTIC_H__
#define __HEURISTIC_H__

#include "common.hpp"
#include "board.hpp"

class Heuristic {
public:
    int score(Board *board, Side side);
};

#endif
