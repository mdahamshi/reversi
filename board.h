#ifndef BOARD_H
#define BOARD_H


#include <iostream>
#include <string>
#include <list>
#include <math.h>

using namespace std;


//board row/col size
#define  SIZE 12
#define BOARD_SIZE (SIZE*SIZE)
#define CENTER (SIZE /2 -1)
//enum that describes the current state in some place
enum state { empty, black , white , possible};
//enum of directions
enum direction {LEFT , left_up , up , right_up , RIGHT , right_down , down , left_down};
// enum of player type
enum side {COMPUTER , HUMAN};
// enum of computer algorithm
enum Method{minimax , alphabeta};


class Player;
class Game;
class Board;


/*a list of the board cells*/
typedef struct s_node
{
    struct s_node* next;
    struct s_node* prev;
    state color;
    int place; //0...143
    s_node(){next=NULL;prev=NULL;color=empty;place=-1;}
} ListNode;

/*the used places (black/white)*/
typedef struct b_node
{
    state color;
    ListNode* ptr;
    b_node(){color=empty;ptr=NULL;}
} ArrNode;

/*the possible places to go*/
typedef struct possible_node
{
    int place; //0..143
    int dir [SIZE];
    struct possible_node* next;
    possible_node(){
        place=-1;
        next=NULL;
    for(int j=0;j<SIZE;j++)
            {
                dir[j]=-1;
            }
    }
}	Possible;

/*holds the best move for the computer*/
typedef struct best
{
    double score;
    Possible move;
    best(){score=0;};
} Best;


class Board
{
private:
    state turn;
    ArrNode board[SIZE*SIZE];
    int V[SIZE][SIZE];
    ListNode *head, *list, *black_end;
    Possible *possHead;
    int black_num, white_num;
    std::list<int> ColHead;
    int flag;
    int PossNumber;
    friend class Play;
public:
    // Constructor , Copy Constructor , Distructor , Operator =
    Board(); /*constructor*/
    Board(Board& source); /* copy constructor */
    ~Board(); /* distructor */
    Board(const Board&);
    Board& operator=(Board& source); /* operator = */
    // Get Functions
    int getV(int r, int c){return V[r][c];} /* return value of V array in [r][c] */
    ListNode* gethead(){return head;} /* return the head of the main list (part of the DS) */
    ArrNode* getboard(){return board;} /* return the board array */
    state getBstate(int i){return this->board[i].color;} /*return the color of the given place*/
    int getPossNum(){return PossNumber;}	 /* return the number of possibles */
    int getWhiteNum(){return white_num;} /*returns the number of whites*/
    int getBlackNum(){return black_num;} /*returns the number of blacks*/
    state getturn(){return turn;}		 /*returns whose turn is now (black/white)*/
    Possible* getPos(){return possHead;} /*returns the head of the Possible nodes List*/
    std::list<int> getcolored(){return ColHead;}
    static state NegColor(state current); /*return negative color*/
    void update_board(state color, int place);/*paint a specific place with the given color*/
    void setTurn(state turn){this->turn=turn;} /*set the current turn*/
    /*check the available directions for each node, based on the current turn color*/
    int check_directions(state* turn , string* text); /*check available directions for current turn and return who won if game ends*/
    /*check the available directions for each node, based on the current turn color*/
    int minicheck_directions(state* turn , string* text); /*for checking directions (sometimes needed for the computer's turn)*/
    int formminicheck_directions(state* turn , int );
    void convert(int original , int* row, int* col); /* convert place of array into row and col , to make access easier */
    void update_locations(ListNode* node); /*update available directions to move*/
    int update_possible(direction direc, int  i, ListNode* node); /*update the possible moves list*/
    void organize(int place); /* organize the main list , sorting it by color(state) */
    Board update_color(Possible* poss, state turn_color); /*after making a move, update the new board*/
    void DeletePoss(); /*clear the possible list*/
    string endgame(); /*return who won*/
    void passturn(){turn=NegColor(turn);} /*skip the turn if has no moves*/
};
#endif // BOARD_H
