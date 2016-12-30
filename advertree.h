#ifndef ADVERTREE_H
#define ADVERTREE_H
#include "constants.h"


class AdverTree
{
public:
    AdverTree()
    {
        front = NULL;
        front_child = NULL;
        front_MM = NULL;
        front_AB = NULL;
    }

    struct Tree_Node
    {
        char nodeboard[SIZE][SIZE];
        string position;
        int depth;
        int value;
        int minmax_value;
        int alpha;
        int beta;
        int ab_value;

        struct Tree_Node *nextSibling;
        struct Tree_Node *firstChild;
        struct Tree_Node *parent;
    };

    //Linkedlist of a particular level in the game tree. Used as a temporary linkedlist for insertion
    struct Child_Queue
    {
        char childboard[SIZE][SIZE];
        string position;

        struct Child_Queue *next;
    };
    struct Log_AB_Queue
    {
        string position;
        int depth;
        int value;
        int alpha;
        int beta;

        struct Log_AB_Queue *next;
    };

    struct Tree_Node *front;
    struct Child_Queue *front_child;
    struct Log_MM_Queue *front_MM;
    struct Log_AB_Queue *front_AB;

    char flip(char);
    void Build_Tree();
    void Build_Root(char board[9][9]);
    void Build_Next_Level(char, int);
    void Insert_Recursive(struct Tree_Node *traverse_tree, char, int);
    void Insert_Log_MM_Queue(string, int, int);
    void Insert_Log_AB_Queue(string, int, int, int, int);
    void Display_Log_MM_Queue();
    void Display_Log_AB_Queue();
    void MinMax();
    int Traverse_Recursive_MinMax(struct Tree_Node *traverse_tree);
    void Alpha_Beta();
    int Traverse_Recursive_AlphaBeta(struct Tree_Node *traverse_tree, int, int);
    void Display_Next_State();
    void Next_State();
    void Add_X_Children(char nodeboard[9][9]);
    void Add_O_Children(char nodeboard[9][9]);
    void Sort_Queue(struct Child_Queue *old_list_front);
    void Find_Left(char, char, int, int, int, int, char nodeboard[9][9]);
    void Find_Right(char, char, int, int, int, int, char nodeboard[9][9]);
    void Find_Up(char, char, int, int, int, int, char nodeboard[9][9]);
    void Find_Down(char, char, int, int, int, int, char nodeboard[9][9]);
    void Find_Diagonal_LeftUp(char, char, int, int, int, int, char nodeboard[9][9]);
    void Find_Diagonal_RightUp(char, char, int, int, int, int, char nodeboard[9][9]);
    void Find_Diagonal_LeftDown(char, char, int, int, int, int, char nodeboard[9][9]);
    void Find_Diagonal_RightDown(char, char, int, int, int, int, char nodeboard[9][9]);
    int Compare_Arrays(char x[9][9], char y[9][9]);
    void Check_All_Directions(char, char new_nodeboard[9][9], int, int);
    int Check_Game_End_Condition(char new_nodeboard[9][9]);
    void Build_Node(char, int, int, int, int, char nodeboard[9][9]);


};

#endif // ADVERTREE_H
