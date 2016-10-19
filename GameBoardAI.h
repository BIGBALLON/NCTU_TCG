#ifndef __GAMEBOARDAI_H__
#define __GAMEBOARDAI_H__

#include <iostream>
#include "Fib2584/MoveDirection.h"
#include "Fib2584/MoveTable.h"
#include "Fib2584/BitBoard.h"
#include "Fib2584/Random.h"

using namespace std;

class GameBoardAI
{
public:
	static const int fibonacci_[32];
private:
	static Random random_;
public:
	GameBoardAI();

	GameBoardAI(const GameBoardAI &src); // add
	GameBoardAI(const int board[4][4]); // add
	unsigned int getAx(int num);	//add
	unsigned int getBox(int num);	//add
	unsigned int getBox2(int num);	//add

	void initialize();
	int move(MoveDirection moveDirection);
	void addRandomTile();
	bool terminated();
	void getArrayBoard(int board[4][4]);
	int getMaxTile();
	void showBoard();
	bool operator==(GameBoardAI gameBoard);
	BitBoard getRow(int row);
	BitBoard getColumn(int column);
	BitBoard restoreRow(BitBoard rowBits, int row);
	BitBoard restoreColumn(BitBoard columnBits, int column);
	int countEmptyTile();
	int getTile(int row, int column);
	int getFibonacci(int index);

private:
	BitBoard board_;
};

#endif