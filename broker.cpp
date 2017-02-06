#include "broker.h"
Broker* Broker::m_Instance = NULL;
Broker::Broker()
{

    gameBoard.initializeBoard();
    QObject::connect(this, SIGNAL(gameStart()),
                     SLOT(onGameStart()));

    currentGame = NULL;
}

Game *Broker::getCurrentGame() const
{
    return currentGame;
}

void Broker::setCurrentGame(Game *value)
{
    currentGame = value;
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


bool Broker::someoneWon()
{
    return currentGame->someoneWon();
}

bool Broker::createGame(int blacktype, int whitetype, int blackalg, int whitealg, int blackdep, int whitedep)
{
    currentGame = new Game(blacktype,whitetype,blackalg,whitealg,blackdep,whitedep);
    currentGame->setGameBoard(&gameBoard);
    updatePossible();
    emit gameStart();
}
void Broker::onGameStart()
{
    if(currentGame->getTurnType() == Constants::PC){
        currentGame->pcMove(currentGame->getTurn());
        cout<<"in ongamestart slot"<<endl;

        flipTurn();
    }
}
void Broker::gotInput(int i, int j )
{
    std::cout<<"now im in got input"<<endl;
    currentGame->gameBoard->checkBoard(Move(i,j),currentGame->getTurn());
    emit updateBoard();     //at end of pc thinking
    flipTurn();

}
void Broker::flipTurn()
{
    if (currentGame->getTurn() == Constants::BLACK)
        currentGame->setTurn(Constants::WHITE);
    else
        currentGame->setTurn(Constants::BLACK);

    if(someoneWon()){
        QCoreApplication::processEvents();
        emit updateBoard();
        emit gameEnd();
        QCoreApplication::processEvents();
        return;
    }
    cout<<"**************************************"<<endl;
    printBoard();
    emit updateBoard();
    QCoreApplication::processEvents();

    if(currentGame->getGameBoard()->noPossibleMove()){
        cout<<"no possible move !"<<endl;
        emit noPossible();
        sleep(1);
        QCoreApplication::processEvents();
        sleep(2);
        flipTurn();
        return;
    }

    if (currentGame->getTurnType() == Constants::PC){
        currentGame->pcMove(currentGame->getTurn());
        QCoreApplication::processEvents();
        flipTurn();
        return;
    }
   emit updateBoard();


}
void Broker::endCurrentGame()
{
    delete currentGame;
    gameBoard.initializeBoard();
    emit gameRestart();
}
