#ifndef GAME_H
#define GAME_H
//#include "constants.h"
#include "player.h"
#include "liveboard.h"


class Game
{
private:
    int game_type;
    int algo;
    int depth;
    int turn;
    Player blackPlayer;
    Player whitePlayer;

    int passRounds;

    int H[SIZE][SIZE]={


{ 1000, -300, 20,  5,10,10,10,10, 5,20, -300,  1000 },
  { -300,-300, -1, -1,-1,-1,-1,-1,-1,-1,  -300, -300 },
  {  20,  -1,   5,  1, 2, 2, 2, 2, 1, 5,    -1,     20 },
  {  5,   -1,   1, -1, 1, 1, 1, 1,-1, 1,   -1,     5 },
  {  10 , -1,   2,  1, 2, 2, 2, 2, 1, 2,   -1,     10 },
  {  10,  -1,   2,  1, 2, 1, 1, 2, 1, 2,   -1,     10 },
  {  10,  -1,   2,  1, 2, 1, 1, 2, 1, 2,   -1,     10 },
  {  10,  -1,   2,  1, 2, 2, 2, 2, 1, 2,   -1,     10 },
  {  5,   -1,   1, -1, 1, 1, 1, 1,-1, 1,   -1,     5 },
  {  20,  -1,   5,  1, 2, 2, 2, 2, 1, 5,    -1,     20  },
 { -300, -300,  -1, -1,-1,-1,-1,-1,-1, -1, -300, -300 },
 { 1000, -300, 20,  5,10,10,10,10, 5, 20, -300,  1000 } };



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
    LiveBoard *gameBoard;
    Game();
    Game(int blacktype, int whitetype, int blackalg, int whitealg, int blackdep, int whitedep);
    int getGame_type() const;
    void updatePossible();
    void setGame_type(int value);
    int getNextTurnColor(){return (getTurn() == Constants::BLACK ? Constants::WHITE : Constants::BLACK);}
    int getAlgo() const;
    void setAlgo(int value);
    int getDepth() const;
    bool someoneWon();
    void setDepth(int value);

    int getTurn() const;
    int getTurnType();
    int checkBoard(Move *move, int kind);
    void set(Move *move,int);
    int Check(Move *move, int incx, int incy, int kind , bool set);
    bool isValid(Move *move, int kind) ;
    void setTurn(int value);
    Best alphabeta(LiveBoard board ,int depth ,int alphaBeta ,Move currentMove);
    void pcMove(int c);
    bool noMoveBoth();
    Best getBestMove(Player player);
    Best minimax(LiveBoard gameBoard ,int depth ,Move);
    LiveBoard *getGameBoard() const;
    void setGameBoard(LiveBoard *value);
    bool legalMove(int currentRow, int currentCol ,int currentTurn);
    Player getWhitePlayer() const;
    void setWhitePlayer(const Player &value);
    int getHeuristicAt(int i){return H[i / SIZE][i % SIZE];}
    double heursticEvaluate(LiveBoard board ,int turn);
    Player getBlackPlayer() const;
    int getTurnDepth(){return (getTurn() == Constants::WHITE ? getWhitePlayer().getDepth() : getBlackPlayer().getDepth()); }
    void setBlackPlayer(const Player &value);

signals:
    void gameUpdateBoard();

};

#endif // GAME_H
