#ifndef GAME_H
#define GAME_H


#include "player.h"


class Game
{
private:
    Board board;
    Player *player1,*player2;
    int game_ended;
public:

    Game(int depth1 , int depth2 , side p1 , side p2){
        game_ended=0;
        player1 = new Player(p1 , black , depth1);
        player2 = new Player(p2 , white , depth2);
    }
    int GameEnd(){return game_ended;}/*check whether game has ended*/
    void GameEnd(int ge){game_ended = ge;} /*determine end of game*/
    void setBoardTurn(state turn){board.setTurn(turn);} /*determine who's playing*/
    Board& getboard(){return board;} /*return a reference for the board*/
    Player getp1(){return *player1;} /*return a pointer to player 1*/
    Player getp2(){return *player2;} /*return a pointer to player 2*/
    ArrNode* getboard1(){return board.getboard() ;} /*return a pointer to the board*/
    void setboard(Board b){board=b;} /*update the board*/
};
#endif // GAME_H
