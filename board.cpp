#include "board.h"

// The Constructor
Board::Board(){
        PossNumber = 0;
        flag = 2;
        turn=black; /*black always starts*/
        // starting board includes 2 blacks and 2 whites
        black_num = 2; white_num = 2;
        head = new ListNode;
        possHead=NULL;
        list = head;
        // the heuristic values array
        int arr[SIZE][SIZE] ={ {-300, 40, -10, -5, -5, -10, 40,  -300},
                          {40, 40,  1, 1, 1,  1, 40, 40},
                          { -10,   1,  5, 2, 2,  5,   1,  -10},
                          {  -5,   1,  2, 1, 1,  2,   1,   -5},
                          {  -5,   1,  2, 1, 1,  2,   1,   -5},
                          { -10,   1,  5, 2, 2,  5,   1,  -10},
                          {40, 40,  1, 1, 1,  1, 40, 40},
                          { -300, 40, -10, -5, -5, -10, 40,  -300}};
        for(int i=0;i<SIZE*SIZE;i++)
            *(*V+i) = *(*arr+i);
        for (int i = 0; i < SIZE*SIZE; i++) /*intialize board with 'empty'*/
            {
                board[i].color = empty;
                list->next = new ListNode;
                list->next->prev = list;
                list = list->next;
                list->color = empty;
                board[i].ptr = list;
                list->place = i;
            }
        list->next = NULL;
        /*first phase has 2 blacks and 2 whites in the center of the board*/
        board[CENTER*SIZE+(CENTER+1)].color = black;
        (board[CENTER*SIZE+(CENTER+1)].ptr)->color = black;

        /*deal with the 1st black*/
        ListNode *node,*temp;
        node = board[CENTER*SIZE+(CENTER+1)].ptr;
        node->next->prev = node->prev;
        node->prev->next = node->next;
        node->next=head->next;
        head->next->prev=node;
        head->next = node;
        node->prev = head;
        black_end = head->next;
        head->prev=NULL;
        /*done dealing with 1st black*/

        board[CENTER*SIZE+CENTER].color = white;
        (board[CENTER*SIZE+CENTER].ptr)->color = white;
        organize(27);
        board[(CENTER+1)*SIZE+CENTER].color = black;
        (board[(CENTER+1)*SIZE+CENTER].ptr)->color = black;
        organize(35);
        board[(CENTER+1)*SIZE+(CENTER+1)].color = white;
        (board[(CENTER+1)*SIZE+(CENTER+1)].ptr)->color = white;
        organize(36);
}

Board::~Board(){
    int p_num = PossNumber;
    ListNode* temp=head;
    ListNode* ptr = temp;
    Possible* temp1=possHead;
    //delete head;
    for(int i=0;i<BOARD_SIZE;i++)
    {
        delete board[i].ptr;
        board[i].ptr=NULL;
    }

    while(p_num>0 && temp1!=NULL){
        temp1=temp1->next;
        delete possHead;
        possHead=temp1;
        p_num--;
    }
    head=NULL;list=NULL;black_end=NULL;possHead=NULL;
}

Board::Board(Board& source){
    Possible* temp=NULL,*temp1=NULL;
    int p_num = source.PossNumber;
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            this->V[i][j] = source.V[i][j];
    this->turn=source.turn;
    temp=source.getPos();
    this->black_num=source.black_num;
    this->white_num=source.white_num;
    this->ColHead=source.ColHead;
    this->flag=source.flag;
    this->PossNumber = source.PossNumber;
    //copy possible list
    //copy head
    if(p_num>0 && temp!=NULL){
        possHead=new Possible();
        possHead->place=temp->place;
        for(int j=0;j<SIZE;j++)
            {
                possHead->dir[j]=temp->dir[j];
            }
    temp=temp->next;
    p_num--;}
    p_num=source.PossNumber;
    while(p_num>0 && temp!=NULL){
        temp1=new Possible();
        temp1->place=temp->place;
        for(int j=0;j<SIZE;j++)
            {
                temp1->dir[j]=temp->dir[j];
            }
        temp1->next=possHead;
        possHead=temp1;
        temp=temp->next;
        p_num--;
    }
    this->head = new ListNode();
    this->list =this->head;
    for (int i = 0; i < SIZE*SIZE; i++) /*intialize board with 'empty'*/
    {
        this->board[i].color = empty;
        this->list->next = new ListNode;
        this->list->next->prev = this->list;
        this->list = this->list->next;
        this->list->color = empty;
        this->board[i].ptr =this-> list;
        this->list->place = i;
    }
    this->list->next = NULL;
    this->black_end = this->head->next;
    ((this->board[source.head->next->place]).color) = black;
    ((this->board[source.head->next->place]).ptr)->color = black;

    /*deal with the 1st black*/
        ListNode *node;
        node = ((this->board[source.head->next->place]).ptr);
        black_end=node;
        if(node->next == NULL)
            node->prev->next = NULL;
        else
        {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        black_end->next=head->next;
        node->next = this->head->next;
        head->next->prev=node;
        this->head->next = node;
        node->prev = this->head;
        this->black_end = node;
        this->head->prev=NULL;
        for (int j = 0; j < SIZE*SIZE; j++) /*intialize board with 'empty'*/
        {
            if((j==source.head->next->place) || (source.board[j].color==empty) || (source.board[j].color==possible) ) continue;
            this->board[j].color = source.board[j].color;
            (this->board[j].ptr)->color = this->board[j].color;
            this->organize(j);
        }

    }

Board& Board::operator=(Board& source)
{
    ListNode* temp=head;
        ListNode* ptr = temp;
        Possible* temp1=possHead;
        for(int i=0;i<SIZE;i++)
            for(int j=0;j<SIZE;j++)
                this->V[i][j] = source.V[i][j];
        //delete head;
        for(int i=0;i<BOARD_SIZE;i++)
        {
            delete board[i].ptr;
            board[i].ptr=NULL;
        }

        while(temp1!=NULL){
            temp1=temp1->next;
            delete possHead;
            possHead=temp1;
        }
        head=NULL;list=NULL;black_end=NULL;possHead=NULL;
        Possible* tempc=NULL,*temp1c=NULL;
        this->turn=source.turn;
    tempc=source.getPos();
    this->black_num=source.black_num;
    this->white_num=source.white_num;
    this->ColHead=source.ColHead;
    this->flag=source.flag;
    this->PossNumber = source.PossNumber;
    //copy possible list
    if(tempc){
        possHead=new Possible();
        possHead->place=tempc->place;
        for(int j=0;j<SIZE;j++)
            {
                possHead->dir[j]=tempc->dir[j];
            }
    tempc=tempc->next;}
    while(tempc!=NULL){
        temp1c=new Possible();
        temp1c->place=tempc->place;
        for(int j=0;j<SIZE;j++)
            {
                temp1c->dir[j]=tempc->dir[j];
            }
        temp1c->next=possHead;
        possHead=temp1c;
        tempc=tempc->next;
    }
    this->head = new ListNode();
    this->list =this->head;

        for (int i = 0; i < SIZE*SIZE; i++) /*intialize board with 'empty'*/
            {
                this->board[i].color = empty;
                this->list->next = new ListNode;
                this->list->next->prev = this->list;
                this->list = this->list->next;
                this->list->color = empty;
                this->board[i].ptr =this-> list;
                this->list->place = i;
            }
        this->list->next = NULL;
        this->black_end = this->head->next;
    ((this->board[source.head->next->place]).color) = black;
        ((this->board[source.head->next->place]).ptr)->color = black;

        /*deal with the 1st black*/
        ListNode *node;
        node = ((this->board[source.head->next->place]).ptr);
        black_end=node;
        if(node->next == NULL)
            node->prev->next = NULL;
        else
        {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        black_end->next=head->next;
        node->next = this->head->next;
        head->next->prev=node;
        this->head->next = node;
        node->prev = this->head;
        this->black_end = node;
        this->head->prev=NULL;
        for (int j = 0; j < SIZE*SIZE; j++) /*intialize board with 'empty'*/
            {
                if((j==source.head->next->place) || (source.board[j].color==empty) || (source.board[j].color==possible) ) continue;
                this->board[j].color = source.board[j].color;
                (this->board[j].ptr)->color = this->board[j].color;
                this->organize(j);
        }
            return *this;

}



state Board::NegColor(state current){
    if(current==white)
        return black;
    else if(current==black)
        return white;
    else return current;
}

void Board::update_board(state color, int place)
{
    ColHead.push_back(place);
    board[place].color = color;
    board[place].ptr->color=color;
    organize(place);
}

int Board::check_directions(state* turn , string* text)
{
    ListNode *temp=NULL;
    state turn2=*turn;
    if(!flag)
    {
        *text = endgame();
        return 1;
    }
    /*determine whether to check available directions for black or for white*/
    if (*turn == black)
        temp = head->next;
    else temp = black_end->next;
    /*color determined. Now update locations for all nodes of current turn*/
    while ((temp) && temp->color == *turn)
    {
        update_locations(temp);
        temp=temp->next;
    }
    if(possHead==NULL)
    {
        flag--;this;
        turn2=NegColor(*turn);
        if(check_directions(&turn2,text))
            return 1;

    }
    else flag=2;
    (*turn)=(turn2);
    return 0;
}


int Board::formminicheck_directions(state* turn , int flag)
{
    ListNode *temp=NULL;
    static int pass=0;
    int check;
    /*determine whether to check available directions for black or for white*/
    if(flag)
    {
        pass=0;
        return 0;
    }
    if (*turn == black)
        temp = head->next;
    else temp = black_end->next;
    /*color determined. Now update locations for all nodes of current turn*/
    while ((temp) && temp->color == *turn)
    {
        update_locations(temp);
        temp=temp->next;
    }
    if(PossNumber==0){
        pass++;
        check=pass;
    }
    else pass=0;
    return pass;
}



int Board::minicheck_directions(state* turn , string* text)
{
    ListNode *temp=NULL;
    /*determine whether to check available directions for black or for white*/
    if (*turn == black)
        temp = head->next;
    else temp = black_end->next;
    /*color determined. Now update locations for all nodes of current turn*/
    while ((temp) && temp->color == *turn)
    {
        update_locations(temp);
        temp=temp->next;
    }
    if(PossNumber==0){
        return 1;
    }
    return 0;
}


void Board::convert(int original , int* row, int* col)
{
    double r=original,c;
    *row = floor(r/SIZE) ;
    *col = original-((*row)*SIZE);
}
/*check available locations and update the board*/
void Board::update_locations(ListNode* node) /**/
{
        int r,c,i;
    /*add the new possible node to the Possible list*/
    /*check left*/
    i = node->place - 1;
    convert(i,&r,&c);
    for(;c>=0;c--,i--)
    {
        //check if the near place is empty
        if (i == node->place - 1 && board[i].color == empty) break;
        if ((node->place) % SIZE == 0)
            break;
        if(update_possible(direction::LEFT,i,node))
            break;
    }
    /*check left-up*/
    i = node->place - SIZE-1;
    convert(i,&r,&c);
    for (; c>=0 && r>=0 ; c--,r--,i -= (SIZE+1))
    {
        if (i == node->place - SIZE - 1 && board[i].color == empty) break;
        if ((node->place) % SIZE == 0)
            break;
        if(update_possible(direction::left_up, i, node))
            break;
        if (i % SIZE == 0)
            break;
    }
    /*check up*/
    i = node->place - SIZE;
    convert(i,&r,&c);
    for (; r>=0 ; r-- , i-=SIZE)
    {
        if (i == node->place - SIZE && board[i].color == empty) break;
        if ((node->place) < SIZE)
            break;
        if(update_possible(direction::up, i, node))
            break;
    }
    /*check right up*/
    i = node->place - SIZE + 1;
    convert(i,&r,&c);
    for (; c<=(SIZE-1) && r>=0 ; r-- , c++ , i -= (SIZE - 1))
    {
        if (i == node->place - SIZE + 1 && board[i].color == empty) break;
        if ((node->place) <SIZE || ((node->place)%SIZE)==(SIZE-1))//need to check
            break;
        if(update_possible(direction::right_up, i, node))
            break;
        if (i % SIZE == SIZE-1)
            break;
    }
    /*check right*/
    i = node->place + 1;
    convert(i,&r,&c);
    for (; c<SIZE ; c++ , i++)
    {
        if (i == node->place + 1 && board[i].color == empty) break;
        if ((node->place) % SIZE == SIZE-1)
            break;
        if(update_possible(direction::RIGHT, i, node))
            break;
    }
    /*check right down*/
    i = node->place + SIZE + 1;
    convert(i,&r,&c);
    for (; c<SIZE && r<SIZE ; c++ , r++ , i += SIZE + 1)
    {
        if (i == node->place + SIZE + 1 && board[i].color == empty)
            break;
        if ((node->place) % SIZE == SIZE-1)
            break;
        if(update_possible(direction::right_down, i, node))
            break;
        if (i % SIZE == SIZE - 1)
            break;
    }
    /*check down*/
    i = node->place+SIZE;
    convert(i,&r,&c);
    for (; r<SIZE ; r++ , i+=SIZE)
    {
        if (i == node->place + SIZE && board[i].color == empty) break;
        if ((node->place) > SIZE*(SIZE-1))
            break;
        if(update_possible(direction::down, i, node))
            break;
    }
    /*check left down*/
    i = node->place + SIZE - 1;
    convert(i,&r,&c);
    for (; c>=0 && r<SIZE ; r++ , c-- , i += (SIZE - 1))
    {
        if (i == node->place + SIZE - 1 && board[i].color == empty)
            break;
        if ((node->place) % SIZE == 0)
            break;
        if(update_possible(direction::left_down, i, node))
            break;
        if (i % SIZE == 0)
            break;
    }
    return;
}

/*add the new possible node to the Possible list*/
int Board::update_possible(direction direc, int  i, ListNode* node)
{
    Possible* temp;temp=NULL;

    /*if near node is same color, don't add*/
    if (board[i].color == node->color)
        return 1;
    /*if reached an empty node after negative color path, add it*/
    if (board[i].color == empty)
    {
        if(possHead==NULL){
            possHead=new Possible();
            temp=possHead;
            board[i].color = possible;
            (temp)->place = i;
            (temp)->dir[direc] = node->place;
            PossNumber++;
            return 1;}
        else{
            temp=new Possible();
            PossNumber++;
            board[i].color = possible;
            (temp)->place = i;
            (temp)->dir[direc] = node->place;
            temp->next=possHead;
            possHead=temp;
            return 1;
        }
    }

    /*handling multiple-path case*/
    /*a node might be already marked as 'possible' but then reached from another path*/
    if (board[i].color == possible)
    {
        Possible* ptr=this->possHead;
        while(ptr->place != i)
            ptr=ptr->next;
        ptr->dir[direc] = node->place;
        return 1;
    }
    return 0;
}

/*given a specific place in the board, put its node in the correct order
    (black -> white -> empty).
    the original place isn't lost because there are pointers from ArrNode to ListNode*/
void Board::organize(int place)
{
    ListNode *node,*temp;
    //check if prev is head.
    if(black_end->place==place)
    {
        black_end=black_end->prev;
        return;
    }
    node = board[place].ptr;
    if(node->next == NULL)
    {
        node->prev->next = NULL;
    }
    else
    {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }
    if(board[place].color==white)
    {
        node->prev = black_end;
        node->next = black_end->next;
        black_end->next->prev = node;
        black_end->next = node;
    }
    if(board[place].color==black)
    {
        node->next = this->head->next;
        this->head->next = node;
        node->next->prev = node;
        node->prev = this->head;
    }
}

//update colors, switch turn and call check_directions.
Board Board::update_color(Possible* poss, state turn_color)
{
    int start, end, countChanges=0;
    ColHead.clear();
    for (int i = 0; i < SIZE; i++){
        switch(i)
        {
        case(0): // left
            if (poss->dir[i] == -1) break;
            start = poss->place;
            end = poss->dir[i];
            for (int j = start+1; j < end; j++){
                update_board(turn_color,j);
                countChanges++;
            }
            break;
        case(1): // left up
            if (poss->dir[i] == -1) break;
            start = poss->place;
            end = poss->dir[i];
            for (int j = start + SIZE+1; j < end; j+=SIZE+1){
                update_board(turn_color,j);
                countChanges++;
            }
            break;
        case(2) : // up
            if (poss->dir[i] == -1) break;
            start = poss->place;
            end = poss->dir[i];
            for (int j = start + SIZE; j < end; j += SIZE){
                update_board(turn_color,j);
                countChanges++;
            }
            break;
        case(3) : // right up
            if (poss->dir[i] == -1) break;
            start = poss->place;
            end = poss->dir[i];
            for (int j = start + SIZE - 1; j < end; j += (SIZE - 1)){
                update_board(turn_color,j);
                countChanges++;
            }
            break;
        case(4) : // right
            if (poss->dir[i] == -1) break;
            start = poss->place;
            end = poss->dir[i];
            //from left to right ( the left direction)
            for (int j = start - 1; j > end; j -= 1){
                update_board(turn_color,j);
                countChanges++;
            }
            break;
        case(5) : // right down
            if (poss->dir[i] == -1) break;
            start = poss->place;
            end = poss->dir[i];
            //from left to right ( the left direction)
            for (int j = start - SIZE - 1; j > end; j -= (SIZE + 1)){
                update_board(turn_color,j);
                countChanges++;
            }
            break;
        case(6) : // down
            if (poss->dir[i] == -1) break;
            start = poss->place;
            end = poss->dir[i];
            //from left to right ( the left direction)
            for (int j = start - SIZE; j > end; j -= SIZE){
            update_board(turn_color,j);
                countChanges++;
            }
            break;
        case(7) : // left down
            if (poss->dir[i] == -1) break;
            start = poss->place;
            end = poss->dir[i];
            //from left to right ( the left direction)
            for (int j = start - SIZE + 1; j > end; j -= (SIZE - 1)){
                update_board(turn_color,j);
                //pictures[j]->ImageLocation = "black-.bmp";
                countChanges++;
            }
            break;
        default: break;
        }
    }
    if (turn_color == black)
    {
        black_num += countChanges + 1;
        white_num -= countChanges;
    }
    else if (turn_color == white){
        white_num += countChanges + 1;
        black_num -= countChanges;
    }
    //PossNumber++;
    update_board(turn_color,start);

    turn=NegColor(turn);
    //call end game check.
    if(white_num + black_num == BOARD_SIZE)
        endgame();//should be deleted

    return *this;
}

/*Clear the Possible list*/
void Board::DeletePoss(){
    Possible* temp = possHead;
    Possible* temp2 = temp;
    while(PossNumber)
    {
        if(board[temp->place].color==possible)
            board[temp->place].color=empty;
        temp = temp->next;
        delete temp2;
        temp2 = temp;
        PossNumber--;
    }
    possHead=NULL;
    PossNumber = 0;
    return;

}

/*at game end, return the winner*/
string Board::endgame()
{
    if(black_num < white_num)
        return "Black Wins";
    else if(white_num < black_num)
        return "White Wins";
    else return "Draw!";
    std::cout<<"game end"<<std::endl;
}

