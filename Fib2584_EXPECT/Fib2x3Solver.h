#ifndef __FIB2X3SOLVER_H__
#define __FIB2X3SOLVER_H__

// include anything you might use
#include <cstdio>
#include <cstring>
#include <cmath>
#include <stdlib.h>
#define SIZE 14*14*14*14*14*14

class Fib2x3Solver
{
public:
	Fib2x3Solver();
	// initialize solver
	void initialize(int argc, char* argv[]);
	// do some action when game over
	double evaluteExpectedScore(int board[2][3]);
	int findBestMove(int board[2][3]);
	
	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/

	int *pos;
	int *bestMove;
	double *expect;
	int up( int board[2][3] );
	int down( int board[2][3] );
	int right( int board[2][3] );
	int left( int board[2][3] );
	int check( int arr[2][3] );
	double dfs( int arr[2][3] );
	void printBoard( int arr[2][3] );
	void copyBoard( int arr[2][3], int tmp[2][3] );
	int cmparr( int arr[2][3], int tmp[2][3] );
	int arr2index( int arr[2][3] );
private:

};

#endif