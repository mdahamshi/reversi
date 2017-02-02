#include "liveboard.h"

LiveBoard::LiveBoard()
{

}
bool LiveBoard::isPossible(int i ,int j)
{
    return possibleBoard[toOneDim(i,j)];
}



int LiveBoard::getColor(int r, int c)
{

    if(whiteBoard[toOneDim(r,c)])
        return Constants::WHITE;
    if(blackBoard[toOneDim(r,c)])
        return Constants::BLACK;
    if(possibleBoard[toOneDim(r,c)])
        return Constants::POSSIBLE;
    return Constants::BLANK;
}
void LiveBoard::initializeBoard()
{
    whiteBoard.reset();
    blackBoard.reset();
    possibleBoard.reset();
    updateColor(CENTER,CENTER,Constants::WHITE);
    updateColor(CENTER+1,CENTER+1,Constants::WHITE);
    updateColor(CENTER,CENTER+1,Constants::BLACK);
    updateColor(CENTER+1,CENTER,Constants::BLACK);
}

void LiveBoard::setPossible(int i,int j)
{
    possibleBoard.set(toOneDim(i,j));
}

void LiveBoard::updateColor(int i, int j, int aColor)
{
    if(isEmpty(i,j)){
        if(aColor == Constants::WHITE)
            whiteBoard.set(toOneDim(i,j));
        else
            blackBoard.set(toOneDim(i,j));
    }
    else
        flipColor(i,j);
}
void LiveBoard::flipColor(int i, int j)
{
    whiteBoard.flip(toOneDim(i,j));
    blackBoard.flip(toOneDim(i,j));

}

int LiveBoard::toOneDim(int i ,int j)
{
    return (i*ROWS +j);
}
bool LiveBoard::isEmpty(int i, int j)
{
    std::bitset<BOARD_SIZE> tmpBoard = whiteBoard | blackBoard;
    return !tmpBoard[toOneDim(i,j)];
}
bool LiveBoard::notEmpty(int i, int j)
{
    return ! isEmpty(i,j);
}

void LiveBoard::printBoard()
{
    cout<<"   ";
    for (int c = 0; c < COLS; c++)
        if(c < 9)
            cout<< c+1 <<"  ";
        else
            cout << c+1 << " ";
    cout<<endl;

    for (int r = 0; r < ROWS; r++)
    {
        if(r < 9)
            cout<< r+1 << setw(3);
        else
            cout << r+1 << setw(2);
        for (int c = 0; c < COLS; c++)
        {
            if(notEmpty(r,c))
            {
                if (getColor(r,c) == Constants::BLACK)
                    cout<< "X";
                else if(getColor(r,c) == Constants::WHITE)
                    cout<< "O";

            }
            else{
                if(isPossible(r,c))
                    cout<<"*";
                else
                    cout<< "-";
            }
            cout<< "  ";
        }
        cout<< endl;
    }
}
