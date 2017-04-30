#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include <iostream>
#include "MoveDirection.h"
#include "MoveTable.h"
#include "BitBoard.h"
#include "Random.h"

using namespace std;

class GameBoard
{
public:
	static const int fibonacci_[32];
private:
	static Random random_;
public:
	GameBoard();
	void initialize();
	int move(MoveDirection moveDirection);
	void addRandomTile();
	bool terminated();
	void getArrayBoard(int board[4][4]);
	int getMaxTile();
	void showBoard();
	bool operator==(GameBoard gameBoard);
private:
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