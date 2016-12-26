#include "player.h"

double Player:: heuristic1(Board board,state turn){
    int i=0;
    int best=0;
    int bscore=0,wscore=0;
    int w = board.getWhiteNum();
        int b = board.getBlackNum();
    for(i=0;i<64;i++){
        if(board.getBstate(i)==black)
            bscore+=board.getV(0,i);
        if(board.getBstate(i)==white)
            wscore+=board.getV(0,i);

    }
    if(turn==white){
        best=bscore-wscore;
        best += (100*(w-b))/(b+w);
        if((w == 0) || (w+b==64 && w<b))
            best = -10000;
        return best;

    }
    else{
        best=wscore-bscore;
        best += (100*(b-w))/(b+w);
        if((b == 0) || (w+b==64 && b<w))
            best = -10000;

        return best;}
    }



    /*determine the best move and return it*/
Best Player::minimax1(Board board , int depth,bool flag, int* i/*place*/)
{
    Board board1;
    state st=this->color;
    Best best,mybest/*bestest*/;
    Possible* pointer;
    string endgame;

    if(depth==getDepth()){
        mybest.score=heuristic1(board,this->color);

        //update mybest.move!!
        return mybest;
    }
    //computer turn, min value
    board.DeletePoss();
    if(depth%2==0) /*COMPUTER*/
    {
        mybest.score=10000;
        board.minicheck_directions(&color,&endgame);
        pointer=board.getPos();
        while(pointer!=NULL && (pointer->place!=-1))
        {
            board1=board;
            best = minimax1(board1.update_color(pointer,this->color) , depth+1,0,&(pointer->place));
            if(mybest.score >= best.score)
                {
                    mybest.score = best.score;
                    mybest.move = *pointer;
                }
            pointer=pointer->next;
        }
        return mybest;
    }
    //opponent turn, max value
    else
    {
        mybest.score=-10000;
        (st)=(Board::NegColor(color));
        board.minicheck_directions(&st,&endgame);
        pointer=board.getPos();
        while(pointer!=NULL && (pointer->place!=-1))
        {
            board1=board;
            best = minimax1(board1.update_color(pointer,Board::NegColor(this->color)) ,depth+1,1,&(pointer->place));
            if(mybest.score <= best.score)
            {
                mybest.score = best.score;
                mybest.move = *pointer;
            }
            pointer=pointer->next;
        }
        return mybest;
    }
}
/*alpha-beta*/
Best Player::alphabeta(Board board , int depth, int* i,int alpeta)
{
    Board board1;
    state st=this->color;
    Best best,mybest/*bestest*/;
    Possible* pointer;
    string endgame;
    if(depth==getDepth())
    {
        mybest.score=heuristic1(board,color);
        //update mybest.move!!
        return mybest;
    }
    //computer turn, min value
    board.DeletePoss();
    if(depth%2==0) /*COMPUTER*/
    {
        //int check_directions(state* turn , string* text)
        mybest.score=100000;
        board.minicheck_directions(&color,&endgame);
        if(board.getPossNum()==0){mybest.score=99;}
        pointer=board.getPos();
        while(pointer!=NULL && (pointer->place!=-1))
        {
            board1=board;
            best = alphabeta(board1.update_color(pointer,this->color) , depth+1,&(pointer->place),mybest.score);
            if(mybest.score >= best.score)
            {
                mybest.score = best.score;
                mybest.move = *pointer;
            }
            if(mybest.score<=alpeta)
                break;
            pointer=pointer->next;
        }
        return mybest;
    }
    //opponent turn, max value
    //if(depth%2==0) /*HUMAN*/
    else
    {
        mybest.score=-100000;
        (st)=(Board::NegColor(color));
        board.minicheck_directions(&st,&endgame);
        if(board.getPossNum()==0){mybest.score=-99;}
        pointer=board.getPos();
        while(pointer!=NULL && (pointer->place!=-1))
        {
            board1=board;
            best = alphabeta(board1.update_color(pointer,Board::NegColor(this->color)) ,depth+1,&(pointer->place),mybest.score);
            if(mybest.score <= best.score)
            {
                mybest.score = best.score;
                mybest.move = *pointer;
            }
            if(mybest.score>=alpeta)
                break;
            pointer=pointer->next;
        }
        return mybest;
    }
}
