#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.hpp"
using namespace std;

class Board {

private:
    bitset<64> black;
    bitset<64> taken;

    void set(Side side, int x, int y);

public:
    Board();
    ~Board();
    Board *copy();

    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    bool onBoard(int x, int y);
    bool occupied(int x, int y);
    bool get(Side side, int x, int y);
    int count(Side side);
    int countBlack();
    int countWhite();
    int countEmpty();

    void setBoard(char data[]);
};

#endif
