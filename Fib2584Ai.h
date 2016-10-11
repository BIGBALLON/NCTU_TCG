#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "Fib2584/MoveDirection.h"

class Fib2584Ai
{
public:
	Fib2584Ai();
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
	MoveDirection generateMove(int board[4][4]);
	// do some action when game over
	void gameOver(int board[4][4], int iScore);

	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/

	int *fibIndex;
	int board_prev[4][4];
	int prev_move;
	
	int moveOne( int board[4][4], MoveDirection iDirection, int& score );
	void printBoard( int board[4][4] );
	bool cmpBoard( int board[4][4], int temp[4][4] );
	void copyBoard( int board[4][4], int temp[4][4] );
	int getEmpty( int board[4][4] );
	int getMaxTile( int board[4][4] );
};

#endif