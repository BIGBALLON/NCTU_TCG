#include "GameBoardAI.h"

const int GameBoardAI::fibonacci_[32] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};
Random GameBoardAI::random_;

GameBoardAI::GameBoardAI():
board_(0)
{
}

GameBoardAI::GameBoardAI(const GameBoardAI &src)
:	board_(src.board_)
{
}

int invFibonacci(const int fib)
{
	for (int i = 0; i < 32; i++) {
		if (GameBoardAI::fibonacci_[i] == fib)
			return i;
	}
	return -1;
}


GameBoardAI::GameBoardAI(const int board[4][4])
:	board_(0)
{
	for (int i = 0; i < 16; i++) {
		int invFib = invFibonacci(board[i / 4][i % 4]);
		board_ = (board_ << 5) | BitBoard(invFib & 0x1f);
	}
}


void GameBoardAI::initialize()
{
	board_ = 0;
	addRandomTile();
	addRandomTile();
}

int GameBoardAI::move(MoveDirection moveDirection)
{
	BitBoard newBoard = 0;
	int score = 0;
	if(moveDirection == MOVE_UP || moveDirection == MOVE_DOWN) {
		for(int i = 0;i < 4;i++) {
			BitBoard tempColumn = 0;
			tempColumn = getColumn(i);
			newBoard |= restoreColumn(MoveTable::move_table.row_move_table_[moveDirection == MOVE_DOWN][tempColumn], i);
			score += MoveTable::move_table.row_move_score_table_[moveDirection == MOVE_DOWN][tempColumn];
		}
	}
	else {
		for(int i = 0;i < 4;i++) {
			BitBoard tempRow = 0;
			tempRow = getRow(i);
			newBoard |= restoreRow(MoveTable::move_table.row_move_table_[moveDirection == MOVE_RIGHT][tempRow], i);
			score += MoveTable::move_table.row_move_score_table_[moveDirection == MOVE_RIGHT][tempRow];
		}
	}
	board_ = newBoard;
	return score;
}

void GameBoardAI::addRandomTile()
{
	int oneTileRate = 6;
	int emptyTileNum = countEmptyTile();
	int randomTileLocation = random_.get_rand_num() % emptyTileNum;
	BitBoard randomTile = (random_.get_rand_num() % 8 < oneTileRate)?0x1:0x3;
	int count = 0;
	for(BitBoard tileMask = 0x1f;tileMask != 0;tileMask <<= 5, randomTile <<= 5) {
		if((board_ & tileMask) != 0)
			continue;
		if(count == randomTileLocation) {
			board_ |= randomTile;
			break;
		}
		count++;
	}
}

int GameBoardAI::countEmptyTile()
{
	int count = 0;
	BitBoard tileMask = 0x1f;
	for(;tileMask != 0;tileMask <<= 5) {
		if((board_ & tileMask) == 0)
			count++;
	}
	return count;
}

bool GameBoardAI::terminated()
{
	bool movable = false;
	BitBoard tempColumn;
	BitBoard tempRow;
	for(int i = 0;i < 4;i++) {
		tempColumn = getColumn(i);
		movable |= MoveTable::move_table.row_can_move_[0][tempColumn];
		movable |= MoveTable::move_table.row_can_move_[1][tempColumn];
		tempRow = getRow(i);
		movable |= MoveTable::move_table.row_can_move_[0][tempRow];
		movable |= MoveTable::move_table.row_can_move_[1][tempRow];
		if(movable)
			break;
	}
	return !movable;
}

void GameBoardAI::getArrayBoard(int board[4][4])
{
	BitBoard tempBoard = board_;
	for(int i = 0;i < 16;i++) {
		board[3 - (i / 4)][3 - (i % 4)] = fibonacci_[(int)(tempBoard & 0x1f)];
		tempBoard = tempBoard >> 5;
	}
}

int GameBoardAI::getMaxTile()
{
	BitBoard countBoard = board_;
	int max_tile = 0;
	for(int i = 0;i < 16;i++) {
		if((countBoard & 0x1f) > max_tile)
			max_tile = countBoard & 0x1f;
		countBoard >>= 5;
	}
	return fibonacci_[max_tile];
}

BitBoard GameBoardAI::getRow( int row )
{
	return board_ >> (row * 20) & 0xfffff;
}

BitBoard GameBoardAI::getColumn( int column )
{
	BitBoard tempBoard = board_ >> (column * 5) & BitBoard(0x0001, 0xf0001f0001f0001f);
	return (tempBoard & BitBoard(0x0001, 0xf000000000000000)) >> 45 |
      	   (tempBoard & BitBoard(0x0000, 0x00001f0000000000)) >> 30 |
      	   (tempBoard & BitBoard(0x0000, 0x0000000001f00000)) >> 15 |
       	   (tempBoard & BitBoard(0x0000, 0x000000000000001f));
}

BitBoard GameBoardAI::restoreRow( BitBoard rowBits, int row )
{
  	return rowBits << (row * 20);
}

BitBoard GameBoardAI::restoreColumn( BitBoard columnBits, int column )
{
  	return ((columnBits & BitBoard(0xf8000)) << 45 |
            (columnBits & BitBoard(0x07c00)) << 30 |
            (columnBits & BitBoard(0x003e0)) << 15 |
            (columnBits & BitBoard(0x0001f)) ) << (column * 5);
}

int GameBoardAI::getTile( int row, int column )
{
	int tile = ((board_ >> (row * 20) & 0xfffff) >> (column * 5)) & 0x1f;
	return fibonacci_[tile];
}

void GameBoardAI::showBoard()
{
  	for(int row = 3;row >= 0;row--) {
   		for(int column = 3;column >= 0;column--)
      		cout << dec << getTile(row, column) << "\t";
    	cout << "\n";
  	}
}

bool GameBoardAI::operator==(GameBoardAI gameBoard)
{
	return board_ == gameBoard.board_;
}
