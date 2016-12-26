#ifndef PLAYER_H
#define PLAYER_H


#include "board.h"

class Player
{
private:
    state color;
    side sd; /*COMPUTER / HUMAN*/
    int depth;
public:
    Player(side s,state c,int d):sd(s),color(c),depth(d){} /*constructor for player*/
    double heuristic1(Board board,state turn); 	/*the heuristic function. Helps minimax decide its move*/
    Best minimax1(Board board , int depth,bool flag, int* i/*place*/); /*move probing algorithm*/
    Best alphabeta(Board board , int depth, int* i,int alpeta); /*fast move proving algorithm*/
    int getDepth(){return depth;} /*return the depth the player set*/
    side getSide(){return sd;} /*return the current player*/
    void setSide(side s){ sd = s;} /*determine the player (COMPUTER / HUMAN)*/
};



#endif // PLAYER_H
