#include "liveboard.h"

std::bitset<BOARD_SIZE> LiveBoard::getPossibleBoard() const
{
    return possibleBoard;
}

std::bitset<BOARD_SIZE> LiveBoard::getBlackBoard() const
{
    return blackBoard;
}

std::bitset<BOARD_SIZE> LiveBoard::getWhiteBoard() const
{
    return whiteBoard;
}

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
int LiveBoard::getColor(int r)
{

    if(whiteBoard[r])
        return Constants::WHITE;
    if(blackBoard[r])
        return Constants::BLACK;
    if(possibleBoard[r])
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
int LiveBoard::Check(Move move, int incx, int incy, int kind , bool toSet)  {
        int opponent;
        int x=move.i;
        int y=move.j;
        if (kind == Constants::BLACK) opponent=Constants::WHITE; else opponent=Constants::BLACK;
        int n_inc=0;
        x+=incx; y+=incy;
        while ((x<SIZE) && (x>=0) && (y<SIZE) && (y>=0) && (getColor(x,y)==opponent)) {
            x+=incx; y+=incy;
            n_inc++;
        }
        if ((n_inc != 0) && (x<SIZE) && (x>=0) && (y<SIZE) && (y>=0) && (getColor(x,y)==kind)) {
             if (toSet)
             for (int j = 1 ; j <= n_inc ; j++) {
                x-=incx; y-=incy;
                 set(Move(x,y),kind);
             }
            return n_inc;
        }
        else return 0;
    }
bool LiveBoard::isValid(Move move, int kind) {
        // check increasing x
        if (Check(move,1,0,kind,false) != 0) return true;
        // check decreasing x
        if (Check(move,-1,0,kind,false) != 0) return true;
        // check increasing y
        if (Check(move,0,1,kind,false) != 0) return true;
        // check decreasing y
        if (Check(move,0,-1,kind,false) != 0) return true;
        // check diagonals
        if (Check(move,1,1,kind,false) != 0) return true;
        if (Check(move,-1,1,kind,false) != 0) return true;
        if (Check(move,1,-1,kind,false) != 0) return true;
        if (Check(move,-1,-1,kind,false) != 0) return true;
        return false;
    }
void LiveBoard::updatePossible(int turnColor)
{

    resetPossible();

    for (int i =0; i < SIZE ;i++)
        for (int j=0; j < SIZE ;j++)
            if(isEmpty(i,j) && isValid(Move(i,j),turnColor)){
                setPossible(i,j);
                possibleList.push_back(Move(i,j));
            }

}
LiveBoard& LiveBoard::operator =(LiveBoard& source)
{
    this->blackBoard = source.getBlackBoard();
    this->whiteBoard = source.getWhiteBoard();
    this->possibleBoard = source.getPossibleBoard();
    this->possibleList = source.possibleList;
}

int LiveBoard::checkBoard(Move move, int kind)
{
        // check increasing x

        int j=Check(move,1,0,kind,true);
        // check decreasing x
        j+=Check(move,-1,0,kind,true);
        // check increasing y
        j+=Check(move,0,1,kind,true);
        // check decreasing y
        j+=Check(move,0,-1,kind,true);
        // check diagonals
        j+=Check(move,1,1,kind,true);
        j+=Check(move,-1,1,kind,true);
        j+=Check(move,1,-1,kind,true);
        j+=Check(move,-1,-1,kind,true);
        if (j != 0) set(move,kind);
//        updatePossible(kind);
        return j;
}
void LiveBoard::set(Move move,int kind)
{
    updateColor(move.i,move.j,kind);
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
            cout<< c <<"  ";
        else
            cout << c << " ";
    cout<<endl;

    for (int r = 0; r < ROWS; r++)
    {
        if(r < 10)
            cout<< r << setw(3);
        else
            cout << r << setw(2);
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
//    cout<<endl;
}
