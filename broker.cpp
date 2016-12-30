#include "broker.h"
Broker* Broker::m_Instance = NULL;
Broker::Broker()
{


}

int Broker::getColor(int i, int j)
{
    return (int)gameBoard.getColor(i,j);
}
void Broker::printBoard()
{
    gameBoard.printBoard();
}
int Broker::getBoardSize(){
    return BOARD_SIZE;
}
void Broker::setColor(int i, int j ,int c)
{
    gameBoard.updateColor(i,j,c);
}
