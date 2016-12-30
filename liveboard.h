#ifndef LIVEBOARD_H
#define LIVEBOARD_H
#include "boards.h"

class LiveBoard : public Boards
{
private:
    std::bitset<BOARD_SIZE> possibleBoard;
public:
    LiveBoard();
    bool isPossible(int,int);
    void resetPossible();
    int getColor(int,int) override;
};


#endif // LIVEBOARD_H
