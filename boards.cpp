#include "boards.h"

Boards::Boards()
{
    initializeBoard();
}

int Boards::toOneDim(int i ,int j)
{
    return (i*ROWS +j);
}

void Boards::updateColor(int i ,int j ,int aColor)
{
    if(aColor == Constants::WHITE)
    {
        myBoard.set(toOneDim(i,j));
    }
    else
    {
        myBoard.reset(toOneDim(i,j));
    }

    filledBoard.set(toOneDim(i,j));
}
void Boards::initializeBoard()
{
    updateColor(CENTER,CENTER,Constants::WHITE);
    updateColor(CENTER+1,CENTER+1,Constants::WHITE);
    updateColor(CENTER,CENTER+1,Constants::BLACK);
    updateColor(CENTER+1,CENTER,Constants::BLACK);
}
int Boards::getColor(int r, int c)
{
    if (! filledBoard[toOneDim(r,c)])
        return Constants::BLANK;
    if ( myBoard[toOneDim(r,c)])
        return Constants::WHITE;
    return Constants::BLACK;
}
bool Boards::notEmpty(int i ,int j)
{
    return filledBoard[toOneDim(i,j)];
}
bool Boards::isEmpty(int i , int j)
{
    return ! filledBoard[toOneDim(i,j)];
}
void Boards::printBoard()
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
                else
                    cout<< "O";
            }
            else
                cout<< "-";
            cout<< "  ";
        }
        cout<< endl;
    }
}
