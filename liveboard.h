#ifndef LIVEBOARD_H
#define LIVEBOARD_H
#include "constants.h"
#include <unistd.h>
#include <bitset>
#include <iomanip>

//int arrr[SIZE][SIZE]={
// { 50, -1,  5, 2, 2, 2, 2, 2, 2, 5, -1,  50 },
// { -1, -10, 1, 1, 1, 1, 1, 1, 1, 1, -10, -1 },
// {  5, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1,    5 },
// {  2, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1,    2 },
// {  2, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1,    2 },
// {  2, 1,   1, 1, 1, 0, 0, 1, 1, 1, 1,    2 },
// {  2, 1,   1, 1, 1, 0, 0, 1, 1, 1, 1,    2 },
// {  2, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1,    2 },
// {  2, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1,    2 },
// {  5, 1,   1, 1, 1, 1, 1, 1, 1, 1, 1,    5  },
// { -1, -10, 1, 1, 1, 1, 1, 1, 1, 1, -10, -1 },
// { 50, -1,  5, 2, 2, 2, 2, 2, 2, 5, -1,  50 } };
enum direction {LEFT , left_up , up , right_up , RIGHT , right_down , down , left_down};

class LiveBoard
{
private:

    std::bitset<BOARD_SIZE> possibleBoard;
    std::bitset<BOARD_SIZE> blackBoard;
    std::bitset<BOARD_SIZE> whiteBoard;

public:
    LiveBoard();
//    int getV(int r, int c){return arrr[r][c];}
    bool isPossible(int,int);




    int toOneDim(int i ,int j);
    void updateColor(int i ,int j ,int aColor);
      void flipColor(int,int);
      void initializeBoard();
      bool notEmpty(int i ,int j);
      bool isEmpty(int i , int j);
      int whiteCount(){return whiteBoard.count();}
      int blackCount(){return blackBoard.count();}
      void setPossible(int,int);
      void resetPossible(){possibleBoard.reset();}
      void printBoard();
      bool noPossibleMove(){return ! possibleBoard.count();}
      void Display_Board();
      virtual int getColor(int r, int c);
      void Initialize_Heuristics();
      void Display_Heuristics();

};


#endif // LIVEBOARD_H
