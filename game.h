#ifndef GAME_H
#define GAME_H
//#include "constants.h"
#include "player.h"
#include "liveboard.h"

typedef struct move {
     int i, j;
      move () {
     }
      move (int a, int b) {
         i = a;
         j = b;
     }
 }Move;
class Game
{
private:
    int game_type;
    int algo;
    int depth;
    int turn;
    Player blackPlayer;
    Player whitePlayer;
    LiveBoard *gameBoard;
    int passRounds;




public:

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

    Game();
    Game(int blacktype, int whitetype, int blackalg, int whitealg, int blackdep, int whitedep);
    int getGame_type() const;
    void updatePossible();
    void setGame_type(int value);
    int getAlgo() const;
    void setAlgo(int value);
    int getDepth() const;
    bool someoneWon();
    void setDepth(int value);
    void flipTurn();
    int getTurn() const;
    int getTurnType();
    int checkBoard(Move *move, int kind);
    void set(Move *move,int);
    int Check(Move *move, int incx, int incy, int kind , bool set);
    bool isValid(Move *move, int kind) ;
    void setTurn(int value);
    void pcMove(int c);
    bool noMoveBoth();
    void getBestMove(Player player);
    void minimax(LiveBoard *gameBoard ,int depth ,int maxDepth);
    LiveBoard *getGameBoard() const;
    void setGameBoard(LiveBoard *value);
    bool legalMove(int currentRow, int currentCol ,int currentTurn);
    Player getWhitePlayer() const;
    void setWhitePlayer(const Player &value);

    Player getBlackPlayer() const;
    void setBlackPlayer(const Player &value);

signals:
    void gameUpdateBoard();

};

#endif // GAME_H
