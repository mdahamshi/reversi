#ifndef BOARDS_H
#define BOARDS_H
#include <unistd.h>
#include <bitset>
#include <iomanip>
#include "constants.h"

class Boards
{


protected:
     int toOneDim(int i ,int j);
     std::bitset<BOARD_SIZE> myBoard;
     std::bitset<BOARD_SIZE> filledBoard;
public:
    Boards();

    void updateColor(int i ,int j ,int aColor);

    void initializeBoard();
    bool notEmpty(int i ,int j);
    bool isEmpty(int i , int j);
    void printBoard();
    void Display_Board();
    virtual int getColor(int r, int c);
    void Initialize_Heuristics();
    void Display_Heuristics();

};

#endif // BOARDS_H
