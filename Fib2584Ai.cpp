#include "Fib2584Ai.h"
#include <stdio.h>

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	return;
}

MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
    return td.Move(board);
}


void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	return td.gameover(board);
}

/**********************************
You can implement any additional functions
you may need.
**********************************/

