#include "game.h"
#include "board.h"
#include "player.h"

int main(){
Game *game=new Game(6 , 6 , COMPUTER , COMPUTER);
std::cout<<"main exit "<<game<<std::endl;
return 0;
}
