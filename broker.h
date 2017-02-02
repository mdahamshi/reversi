#ifndef BROKER_H
#define BROKER_H

#include <QObject>
#include <QQuickItem>
#include <QQmlEngine>
//#include "constants.h"
//#include "liveboard.h"
#include "game.h"
//#include "player.h"
#define blockSize  50
#define maxColumn  12
#define maxRow 12
#define maxIndex  maxColumn * maxRow


class Broker: public QObject
{
    Q_OBJECT


public:

    Broker();
    LiveBoard gameBoard;
    Game *currentGame ;


    static  Broker *  m_Instance;
    static Broker *getInstance(){
        if (! m_Instance)
            return new Broker();

        return m_Instance;
    }
    static void declareQML() {
               qmlRegisterType<Broker>("reversi", 1, 0, "Broker");
           }
    Q_INVOKABLE int getColor(int,int);
    Q_INVOKABLE void printBoard();
    Q_INVOKABLE int getBoardSize();
    Q_INVOKABLE int getWhiteCount(){return gameBoard.whiteCount();}
    Q_INVOKABLE int getBlackCount(){return gameBoard.blackCount();}
    Q_INVOKABLE void setColor(int,int,int);
    Q_INVOKABLE void testConnection(){updateBoard();}
    Q_INVOKABLE void gotInput(int i, int j );
    Q_INVOKABLE bool createGame(int blacktype, int whitetype, int blackalg, int whitealg, int blackdep, int whitedep);
    Q_INVOKABLE void endCurrentGame();
    Q_INVOKABLE int getTurn(){return currentGame->getTurn();}
    Game *getCurrentGame() const;
    bool someoneWon();
    void flipTurn();
    void updatePossible(){currentGame->updatePossible(); emit updateBoard();}
    void setCurrentGame(Game *value);


    public slots:
     void onGameStart();

signals:
    void updateBoard();
    void gameEnd();
    void pcThinking();
    void yourTurn();
    void pcPass();
    void gameStart();
    void gameRestart();


};

#endif // BROKER_H
