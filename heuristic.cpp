#include "heuristic.hpp"

Heuristic::Heuristic(Side s) {
    side = s;
    otherSide = (s == BLACK) ? WHITE : BLACK;
}

int Heuristic::score(Board *board) {
    // The simple scheme of +1 for our color, -1 for their color
    int basicCount = board->count(side) - board->count(otherSide);
    return basicCount;
}
