#include "liveboard.h"

LiveBoard::LiveBoard()
{

}
bool LiveBoard::isPossible(int i ,int j)
{
    return possibleBoard[toOneDim(i,j)];
}

void LiveBoard::resetPossible()
{
    possibleBoard.reset();
}
int LiveBoard::getColor(int r, int c)
{
    if (! filledBoard[toOneDim(r,c)])
    {
        if (! possibleBoard[toOneDim(r,c)])
            return Constants::BLANK;
        else
            return Constants::POSSIBLE;
    }
    if ( myBoard[toOneDim(r,c)])
        return Constants::WHITE;
    return Constants::BLACK;
}
