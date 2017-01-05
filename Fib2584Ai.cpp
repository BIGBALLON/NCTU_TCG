#include "Fib2584Ai.h"
#include <stdio.h>

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
	return;
}


MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	if ( td.trainMode ){
		return td.Move(board);
	}else{
		return td.MovePlay(board);
	} 
}


int Fib2584Ai::generateEvilMove(int board[4][4])
{
    //return rand() % 16;
    return td.generateEvilMove(board);

}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	td.gameover(board);
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
