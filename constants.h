#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QObject>
#include <iostream>
#include <string>
#include <QQuickItem>
#include <QQmlEngine>
#define  SIZE 12
#define BOARD_SIZE (SIZE*SIZE)
#define CENTER (SIZE /2 -1)
#define ROWS 12
#define COLS 12
using namespace std;

typedef struct move {
     int i, j;
      move () {
     }
      move (int a, int b) {
         i = a;
         j = b;
     }
 }Move;
typedef struct best {
     Move bestMove;
     int score;
      best () {
     }
      best (Move m ,int s) {
         bestMove.i = m.i;
         bestMove.j = m.j;
         score = s;
     }
 }Best;


class Constants : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rowNumber READ rowNumber )
    Q_PROPERTY(int colNumber READ colNumber )

public:
    static const int board_size = BOARD_SIZE;
    static const int myrowNumber = SIZE;
    static const int mycolNumber = SIZE;
    static int const rowNumber(){return myrowNumber;}
    static int const colNumber(){return mycolNumber;}
    Q_ENUMS(color)
    enum color{
        BLANK,
        WHITE,
        BLACK,
        POSSIBLE
    };
    enum gameType{
        PLAYER_VS_PLAYER,
        PLAYER_VS_PC,
        PC_VS_PC
    };
    enum algorithm{
        NONE,
        MINIMAX,
        ALPHA_BETA,
        BOTH
    };
    enum playerType{
        HUMAN,
        PC
    };

    static  Constants *  m_Instance;
    static Constants *getInstance(){
        if (! m_Instance)
            return new Constants();

        return m_Instance;
    }




    static void QmlDec()
    {
        qmlRegisterType<Constants>("reversi", 1, 0, "Constants");
    }

    explicit Constants(QObject *parent = 0);


signals:

public slots:
};


#endif // CONSTANTS_H
