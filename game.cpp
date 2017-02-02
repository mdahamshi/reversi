#include "game.h"

int Game::getGame_type() const
{
    return game_type;
}

void Game::setGame_type(int value)
{
    game_type = value;
}

int Game::getAlgo() const
{
    return algo;
}

void Game::setAlgo(int value)
{
    algo = value;
}

int Game::getDepth() const
{
    return depth;
}

void Game::setDepth(int value)
{
    depth = value;
}

int Game::getTurn() const
{
    return turn;
}

void Game::setTurn(int value)
{
    turn = value;
}

LiveBoard *Game::getGameBoard() const
{
    return gameBoard;
}

void Game::setGameBoard(LiveBoard *value)
{
    gameBoard = value;
}

Player Game::getWhitePlayer() const
{
    return whitePlayer;
}

void Game::setWhitePlayer(const Player &value)
{
    whitePlayer = value;
}

Player Game::getBlackPlayer() const
{
    return blackPlayer;
}

void Game::setBlackPlayer(const Player &value)
{
    blackPlayer = value;
}

Game::Game()
{

}
Game::Game(int blacktype, int whitetype, int blackalg, int whitealg, int blackdep, int whitedep)
{
    blackPlayer.setAlg(blackalg);
    blackPlayer.setType(blacktype);
    blackPlayer.setDepth(blackdep);
    blackPlayer.setColor(Constants::BLACK);
    whitePlayer.setAlg(whitealg);
    whitePlayer.setType(whitetype);
    passRounds = 0;
    whitePlayer.setDepth(whitedep);
    whitePlayer.setColor(Constants::WHITE);
    if (whitetype == Constants::PC && blacktype == Constants::PC)
        game_type = PC_VS_PC;
    else if (whitetype == Constants::HUMAN && blacktype == Constants::HUMAN)
        game_type = PLAYER_VS_PLAYER;
    else
        game_type = PLAYER_VS_PC;
    turn = Constants::BLACK;


    std::cout<<blacktype<<blackdep<<blackalg<<whitetype<<whitedep<<whitealg<<endl;






}
void Game::updatePossible()
{
    int turnColor = getTurn();
    gameBoard->resetPossible();
    for (int i =0; i < SIZE ;i++)
        for (int j=0; j < SIZE ;j++)
            if(isValid(new Move(i,j),turnColor))
                gameBoard->setPossible(i,j);

}
void Game::flipTurn()
{
    if (getTurn() == Constants::BLACK){
        setTurn(Constants::WHITE);
        if (whitePlayer.getType() == Constants::PC)
            pcMove(Constants::WHITE);
        else
            updatePossible();

        return;
    }
    else{
        setTurn(Constants::BLACK);
        if (blackPlayer.getType() == Constants::PC)
            pcMove(Constants::BLACK);
        else
            updatePossible();
        return;
    }

}
int Game::getTurnType()
{
    if(getTurn() == Constants::BLACK)
        return blackPlayer.getType();
    else
        return whitePlayer.getType();
}

void Game::pcMove(int color)
{
    sleep(1);
    std::cout<<"pc move now!"<<std::endl;
    if(color == Constants::WHITE)
    {
        getBestMove(whitePlayer);
    }
    else
    {
        getBestMove(blackPlayer);
    }


}
bool Game::someoneWon()
{
    if(gameBoard->blackCount() == 0 || gameBoard->whiteCount() == 0 ||
            gameBoard->blackCount() + gameBoard->whiteCount() == BOARD_SIZE || noMoveBoth())
        return true;
    return false;
}
bool Game::noMoveBoth()
{
    updatePossible();
    if(gameBoard->noPossibleMove())
        passRounds++;
    else
        passRounds=0;
    if(passRounds > 1)
        return true;
}

int Game::Check(Move *move, int incx, int incy, int kind , bool toSet)  {
        int opponent;
        int x=move->i;
        int y=move->j;
        if (kind == Constants::BLACK) opponent=Constants::WHITE; else opponent=Constants::BLACK;
        int n_inc=0;
        x+=incx; y+=incy;
        while ((x<SIZE) && (x>=0) && (y<SIZE) && (y>=0) && (gameBoard->getColor(x,y)==opponent)) {
            x+=incx; y+=incy;
            n_inc++;
        }
        if ((n_inc != 0) && (x<SIZE) && (x>=0) && (y<SIZE) && (y>=0) && (gameBoard->getColor(x,y)==kind)) {
             if (toSet)
             for (int j = 1 ; j <= n_inc ; j++) {
                x-=incx; y-=incy;
                 set(new Move(x,y),kind);
             }
            return n_inc;
        }
        else return 0;
    }
bool Game::isValid(Move *move, int kind) {
        // check increasing x
        if (Check(move,1,0,kind,false) != 0) return true;
        // check decreasing x
        if (Check(move,-1,0,kind,false) != 0) return true;
        // check increasing y
        if (Check(move,0,1,kind,false) != 0) return true;
        // check decreasing y
        if (Check(move,0,-1,kind,false) != 0) return true;
        // check diagonals
        if (Check(move,1,1,kind,false) != 0) return true;
        if (Check(move,-1,1,kind,false) != 0) return true;
        if (Check(move,1,-1,kind,false) != 0) return true;
        if (Check(move,-1,-1,kind,false) != 0) return true;
        return false;
    }

int Game::checkBoard(Move *move, int kind)
{
        // check increasing x
        int j=Check(move,1,0,kind,true);
        // check decreasing x
        j+=Check(move,-1,0,kind,true);
        // check increasing y
        j+=Check(move,0,1,kind,true);
        // check decreasing y
        j+=Check(move,0,-1,kind,true);
        // check diagonals
        j+=Check(move,1,1,kind,true);
        j+=Check(move,-1,1,kind,true);
        j+=Check(move,1,-1,kind,true);
        j+=Check(move,-1,-1,kind,true);
        if (j != 0) set(move,kind);
        return j;
}
void Game::set(Move *move,int kind)
{
    gameBoard->updateColor(move->i,move->j,kind);
}

void Game::getBestMove(Player player)
{
//    if (player.getAlg() == Constants::MINIMAX)
//        minimax(player.getColor() ,player.getDepth());
//    else
//        alphabet(player.getColor(),player.getDepth());
}
