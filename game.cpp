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
    gameBoard->updatePossible(getTurn());
//    cout<<"checked possible "<<gameBoard->noPossibleMove()<<" "<<gameBoard->poosibleCount()<< endl;

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
//    sleep(1);
    Move bestMove;
//    std::cout<<"pc move now!"<<std::endl;
    if(color == Constants::WHITE)
    {
        bestMove = getBestMove(whitePlayer).bestMove;
        gameBoard->checkBoard(bestMove ,getTurn());
    }
    else
    {
        bestMove = getBestMove(blackPlayer).bestMove;
        gameBoard->checkBoard(bestMove ,getTurn());
    }


}
bool Game::someoneWon()
{
    if(gameBoard->blackCount() == 0 || gameBoard->whiteCount() == 0 ||
            gameBoard->blackCount() + gameBoard->whiteCount() == BOARD_SIZE || noMoveBoth()){
        cout<<"black depth:"<<getBlackPlayer().getDepth()<<" white depth:"<<getWhitePlayer().getDepth()<< endl;
        return true;
    }
    return false;
}
bool Game::noMoveBoth()
{
    updatePossible();
    if(gameBoard->noPossibleMove())
        passRounds++;
    else
        passRounds=0;
    if(passRounds > 1){
        cout<<"no move both true !"<<endl;
        return true;
    }
    return false;
}



Best Game::getBestMove(Player player)
{
    if (player.getAlg() == Constants::MINIMAX){
        LiveBoard board = *gameBoard;
        Best b = minimax(board ,0 ,Move(board.possibleList.front()));
        cout<<"minimax choose: "<<b.bestMove.i<<","<<b.bestMove.j<<" score:"<<b.score<<
              " turn: "<<(getTurn() == Constants::BLACK ? "black":"white")<< endl<<endl<<endl;
        return b;
    }
    else
    {
        LiveBoard board = *gameBoard;
        Best b = alphabeta(board ,0 ,10000 ,Move(board.possibleList.front()));
        cout<<"alphabeta choose: "<<b.bestMove.i<<","<<b.bestMove.j<<" score:"<<b.score<<
              " turn: "<<(getTurn() == Constants::BLACK ? "black":"white")<< endl<<endl<<endl;
        return b;
    }
}
double Game::heursticEvaluate(LiveBoard board ,int turn)
{
    int i=0 ,bestScore=0 ,blackScore=0 ,whiteScroe=0 ;
    int whiteCount = board.whiteCount() ,blackCount = board.blackCount();

    for (i=0 ;i < BOARD_SIZE ;i++)
    {
        if(board.getColor(i) == Constants::BLACK)
            blackScore += getHeuristicAt(i);
        if(board.getColor(i) == Constants::WHITE)
            whiteScroe += getHeuristicAt(i);
    }
    if(turn == Constants::WHITE)
    {
        bestScore = whiteScroe -blackScore ;
        bestScore += (100*(whiteCount - blackCount) / (whiteCount + blackCount));
        if(whiteCount == 0 || (whiteCount+blackCount == BOARD_SIZE
                               && whiteCount < blackCount))
            bestScore = -10000;
        return bestScore;
    }
    else
    {

        bestScore = blackScore -whiteScroe ;
        bestScore += (100*(blackCount - whiteCount) / (whiteCount + blackCount));
        if(blackCount == 0 || (whiteCount+blackCount == BOARD_SIZE
                               && blackCount < whiteCount))
            bestScore = -10000;
        return bestScore;
    }
}
Best Game::minimax(LiveBoard board, int depth ,Move currentMove)
{
    LiveBoard newBoard;
    Best currentBest, theBest;


    if(depth == getTurnDepth())
    {
        theBest.score = heursticEvaluate(board ,getTurn());
//        cout<<"reached turn depth:"<<getTurnDepth()<<" turn: "<<
//              (getTurn() == Constants::BLACK ? "black":"white")
//           <<" score:"<<theBest.score<<"move:"<<currentMove.i<<","<<
//             currentMove.j<<" b/w:"<<board.blackCount()<<","<<board.whiteCount()<<endl;
        theBest.bestMove = currentMove;
        return theBest;
    }

    if(depth % 2 == 0)
    {
        theBest.score = -10000;

        board.updatePossible(getTurn());
//        if(depth == 0)
//        {
//            theBest.bestMove.i = gameBoard.possibleList.front().i;
//            theBest.bestMove.j = gameBoard.possibleList.front().j;
//        }
        for (Move possibleMove : board.possibleList)
        {
            newBoard = board;
            newBoard.checkBoard(possibleMove ,getTurn());
            if(depth == 0)
            {
                currentBest = minimax(newBoard ,depth + 1 ,possibleMove );
            }
            else
            {
                currentBest = minimax(newBoard ,depth + 1 ,currentMove );
            }
//            cout<<"minmax checked: "<<possibleMove.i<<","<<possibleMove.j<<" depth:"<<depth<<
//                  " got score:"<<currentBest.score<<
//                  " turn: "<<(getTurn() == Constants::BLACK ? "black":"white")<<endl;
//            newBoard.printBoard();
            if(theBest.score <= currentBest.score)
            {
                theBest.score = currentBest.score;
                theBest.bestMove.i = possibleMove.i;
                theBest.bestMove.j = possibleMove.j;

            }
        }
        return theBest;
    }
    else
    {
        theBest.score = 10000;
        board.updatePossible(getNextTurnColor());

        for (Move possibleMove : board.possibleList)
        {
            newBoard = board;

            newBoard.checkBoard(possibleMove ,getNextTurnColor());
            currentBest = minimax(newBoard ,depth + 1,currentMove);
//            cout<<"minmax checked: "<<possibleMove.i<<","<<possibleMove.j<<" depth:"<<depth<<
//                  " got score:"<<currentBest.score<<
//                  " turn: "<<(getTurn() == Constants::BLACK ? "black":"white")<<endl;
//            newBoard.printBoard();
            if(theBest.score >= currentBest.score)
            {
                theBest.score = currentBest.score;
                theBest.bestMove.i = currentMove.i;
                theBest.bestMove.j = currentMove.j;
            }
        }
        return theBest;
    }

}

Best Game::alphabeta(LiveBoard board ,int depth ,int alphaBeta ,Move currentMove)
{
    LiveBoard newBoard;
    Best currentBest, theBest;


    if(depth == getTurnDepth())
    {
        theBest.score = heursticEvaluate(board ,getTurn());
//        cout<<"reached turn depth:"<<getTurnDepth()<<" turn: "<<
//              (getTurn() == Constants::BLACK ? "black":"white")
//           <<" score:"<<theBest.score<<"move:"<<currentMove.i<<","<<
//             currentMove.j<<" b/w:"<<board.blackCount()<<","<<board.whiteCount()<<endl;
        theBest.bestMove = currentMove;
        return theBest;
    }

    if(depth % 2 == 0)
    {
        theBest.score = -10000;

        board.updatePossible(getTurn());
//        if(depth == 0)
//        {
//            theBest.bestMove.i = gameBoard.possibleList.front().i;
//            theBest.bestMove.j = gameBoard.possibleList.front().j;
//        }
        for (Move possibleMove : board.possibleList)
        {
            newBoard = board;
            newBoard.checkBoard(possibleMove ,getTurn());
            if(depth == 0)
            {
                currentBest = alphabeta(newBoard ,depth + 1,theBest.score ,possibleMove );
            }
            else
            {
                currentBest = alphabeta(newBoard ,depth + 1,theBest.score ,currentMove );
            }
//            cout<<"minmax checked: "<<possibleMove.i<<","<<possibleMove.j<<" depth:"<<depth<<
//                  " got score:"<<currentBest.score<<
//                  " turn: "<<(getTurn() == Constants::BLACK ? "black":"white")<<endl;
//            newBoard.printBoard();
            if(theBest.score <= currentBest.score)
            {
                theBest.score = currentBest.score;
                theBest.bestMove.i = possibleMove.i;
                theBest.bestMove.j = possibleMove.j;

            }
            if(theBest.score >= alphaBeta)
                break;
        }
        return theBest;
    }
    else
    {
        theBest.score = 10000;
        board.updatePossible(getNextTurnColor());

        for (Move possibleMove : board.possibleList)
        {
            newBoard = board;

            newBoard.checkBoard(possibleMove ,getNextTurnColor());
            currentBest = alphabeta(newBoard ,depth + 1, theBest.score,currentMove);
//            cout<<"minmax checked: "<<possibleMove.i<<","<<possibleMove.j<<" depth:"<<depth<<
//                  " got score:"<<currentBest.score<<
//                  " turn: "<<(getTurn() == Constants::BLACK ? "black":"white")<<endl;
//            newBoard.printBoard();
            if(theBest.score >= currentBest.score)
            {
                theBest.score = currentBest.score;
                theBest.bestMove.i = currentMove.i;
                theBest.bestMove.j = currentMove.j;
            }
            if(theBest.score <= alphaBeta)
                break;
        }
        return theBest;
    }
}
