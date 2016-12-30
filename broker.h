#ifndef BROKER_H
#define BROKER_H

#include <QObject>
#include <QQuickItem>
#include <QQmlEngine>
#include "constants.h"
#include "liveboard.h"
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
    Q_INVOKABLE void setColor(int,int,int);
    Q_INVOKABLE void testConnection(){updateBoard();}
signals:
    void updateBoard();
};

#endif // BROKER_H
