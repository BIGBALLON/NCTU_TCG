#include "GameBoardAI.h"
#include <stdio.h>
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
		board_ = (board_ << 5) | BitBoardAI(invFib & 0x1f);
	}
}


void GameBoardAI::initialize()
{
	board_ = 0;
	cnt = 0;
	addRandomTile();
	addRandomTile();
}

int GameBoardAI::move(MoveDirection moveDirection)
{
	BitBoardAI newBoard = 0;
	int score = 0;
	if(moveDirection == MOVE_UP || moveDirection == MOVE_DOWN) {
		for(int i = 0;i < 4;i++) {
			BitBoardAI tempColumn = 0;
			tempColumn = getColumn(i);
			newBoard |= restoreColumn(MoveTable::move_table.row_move_table_[moveDirection == MOVE_DOWN][tempColumn], i);
			score += MoveTable::move_table.row_move_score_table_[moveDirection == MOVE_DOWN][tempColumn];
		}
	}
	else {
		for(int i = 0;i < 4;i++) {
			BitBoardAI tempRow = 0;
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
	cnt++;
	int emptyTileNum = countEmptyTile();
	int randomTileLocation = random_.get_rand_num() % emptyTileNum;
	//BitBoardAI randomTile = (random_.get_rand_num() % 8 < oneTileRate)?0x1:0x3;
	BitBoardAI randomTile = 0x1;
	if( cnt == 4 ){
		randomTile = 0x3;
		cnt %= 4;
	}
	
	int count = 0;
	for(BitBoardAI tileMask = 0x1f;tileMask != 0;tileMask <<= 5, randomTile <<= 5) {
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
	BitBoardAI tileMask = 0x1f;
	for(;tileMask != 0;tileMask <<= 5) {
		if((board_ & tileMask) == 0)
			count++;
	}
	return count;
}

bool GameBoardAI::terminated()
{
	bool movable = false;
	BitBoardAI tempColumn;
	BitBoardAI tempRow;
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
	BitBoardAI tempBoard = board_;
	for(int i = 0;i < 16;i++) {
		board[3 - (i / 4)][3 - (i % 4)] = fibonacci_[(int)(tempBoard & 0x1f)];
		tempBoard = tempBoard >> 5;
	}
}

int GameBoardAI::getMaxTile()
{
	BitBoardAI countBoard = board_;
	int max_tile = 0;
	for(int i = 0;i < 16;i++) {
		if((countBoard & 0x1f) > max_tile)
			max_tile = countBoard & 0x1f;
		countBoard >>= 5;
	}
	return fibonacci_[max_tile];
}

BitBoardAI GameBoardAI::getColumn( int column )
{
	BitBoardAI tempBoard = board_ >> (column * 5) & BitBoardAI(0x0001, 0xf0001f0001f0001f);
	return (tempBoard & BitBoardAI(0x0001, 0xf000000000000000)) >> 45 |
      	   (tempBoard & BitBoardAI(0x0000, 0x00001f0000000000)) >> 30 |
      	   (tempBoard & BitBoardAI(0x0000, 0x0000000001f00000)) >> 15 |
       	   (tempBoard & BitBoardAI(0x0000, 0x000000000000001f));
}

BitBoardAI GameBoardAI::getRow( int row )
{
	return board_ >> (row * 20) & 0xfffff;
}

unsigned int GameBoardAI::getLine( int num )
{
	unsigned int result = 0;
	unsigned long long boardLeft = board_.get_left();
	unsigned long long boardRight = board_.get_right();
	if ( num == 0 ){
		result = ( boardLeft << 4 ) | ( boardRight >> 60 & 0xf );
	}else if ( num == 1 ){
		result = boardRight >> 40 & 0xfffff;
	}else if( num == 2 ){
		result = boardRight >> 20 & 0xfffff;
	}else if( num == 3 ){
		result = boardRight & 0xfffff;
	}else if( num == 4 ){
		result = boardLeft >> 11 & 0x1f;
		result <<= 5;
		result |= boardRight >> 55 & 0x1f ;
		result <<= 5;
		result |= boardRight >> 35 & 0x1f ;
		result <<= 5;
		result |= boardRight >> 15 & 0x1f ;
	}else if( num == 5 ){
		result = boardLeft >> 6 & 0x1f;
		result <<= 5;
		result |= boardRight >> 50 & 0x1f ;
		result <<= 5;
		result |= boardRight >> 30 & 0x1f ;
		result <<= 5;
		result |= boardRight >> 10 & 0x1f ;
	}else if( num == 6 ){
		result = boardLeft >> 1 & 0x1f;
		result <<= 5;
		result |= boardRight >> 45 & 0x1f ;
		result <<= 5;
		result |= boardRight >> 25 & 0x1f ;
		result <<= 5;
		result |= boardRight >> 5 & 0x1f ;
	}else if( num == 7 ){
		result = ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
		result <<= 5;
		result |= boardRight >> 40 & 0x1f ;
		result <<= 5;
		result |= boardRight >> 20 & 0x1f ;
		result <<= 5;
		result |= boardRight & 0x1f ;
	}
	return result;
}


unsigned int GameBoardAI::getAx( int num )
{
	unsigned int result = 0;
	unsigned long long boardLeft = board_.get_left();
	unsigned long long boardRight = board_.get_right();
	if ( num == 0 ){
		result = ( boardRight >> 50 & 0x1f );
		result = result * 22 + ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
		result = result * 22 + ( boardLeft >> 1 & 0x1f );
		result = result * 22 + ( boardLeft >> 6 & 0x1f );
		result = result * 22 + ( boardLeft >> 11 & 0x1f );
	}else if ( num == 1 ){
		result = boardRight >> 45 & 0x1f;
		result = result * 22 + ( boardLeft >> 1 & 0x1f );
		result = result * 22 + ( boardRight & 0x1f );
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
	}else if( num == 2 ){
		result = boardRight >> 25 & 0x1f;
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight >> 15 & 0x1f );
		result = result * 22 + ( boardRight >> 10 & 0x1f );
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( boardRight & 0x1f );
	}else if( num == 3 ){
		result = boardRight >> 30 & 0x1f;
		result = result * 22 + ( boardRight >> 10 & 0x1f );
		result = result * 22 + ( boardLeft >> 11 & 0x1f );
		result = result * 22 + ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( boardRight >> 35 & 0x1f );
		result = result * 22 + ( boardRight >> 15 & 0x1f );
	}else if( num == 4 ){
		result = boardRight >> 45 & 0x1f;
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( boardLeft >> 11 & 0x1f );
		result = result * 22 + ( boardLeft >> 6 & 0x1f );
		result = result * 22 + ( boardLeft >> 1 & 0x1f );
		result = result * 22 + ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
	}else if( num == 5 ){
		result = boardRight >> 25 & 0x1f;
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight  & 0x1f );
	}else if( num == 6 ){
		result = boardRight >> 30 & 0x1f;
		result = result * 22 + ( boardRight >> 35 & 0x1f );
		result = result * 22 + ( boardRight & 0x1f );
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( boardRight >> 10 & 0x1f );
		result = result * 22 + ( boardRight >> 15 & 0x1f );
	}else if( num == 7 ){
		result = boardRight >> 50 & 0x1f;
		result = result * 22 + ( boardLeft >> 6 & 0x1f );
		result = result * 22 + ( boardRight >> 15 & 0x1f );
		result = result * 22 + ( boardRight >> 35 & 0x1f );
		result = result * 22 + ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( boardLeft >> 11 & 0x1f );
	}
	return result;
}

unsigned int GameBoardAI::getAx2( int num )
{
	unsigned int result = 0;
	unsigned long long boardLeft = board_.get_left();
	unsigned long long boardRight = board_.get_right();
	if ( num == 0 ){
		result = boardRight >> 15 & 0x1f;
		result = result * 22 + ( boardRight >> 10 & 0x1f );
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( boardRight & 0x1f );
		result = result * 22 + ( boardRight >> 35 & 0x1f );
		result = result * 22 + ( boardRight >> 30 & 0x1f );
	}else if ( num == 1 ){
		result = boardLeft >> 11 & 0x1f;
		result = result * 22 + ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( boardRight >> 35 & 0x1f );
		result = result * 22 + ( boardRight >> 15 & 0x1f );
		result = result * 22 + ( boardLeft >> 6 & 0x1f );
		result = result * 22 + ( boardRight >> 50 & 0x1f );
	}else if( num == 2 ){
		result = ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
		result = result * 22 + ( boardLeft >> 1 & 0x1f );
		result = result * 22 + ( boardLeft >> 6 & 0x1f );
		result = result * 22 + ( boardLeft >> 11 & 0x1f );
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( boardRight >> 45 & 0x1f );
	}else if( num == 3 ){
		result = boardRight & 0x1f;
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( boardRight >> 25 & 0x1f );
	}else if( num == 4 ){
		result = boardRight  & 0x1f;
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( boardRight >> 10 & 0x1f );
		result = result * 22 + ( boardRight >> 15 & 0x1f );
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight >> 25 & 0x1f );
	}else if( num == 5 ){
		result = boardRight >> 15 & 0x1f;
		result = result * 22 + ( boardRight >> 35 & 0x1f );
		result = result * 22 + ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( boardLeft >> 11 & 0x1f );
		result = result * 22 + ( boardRight >> 10 & 0x1f );
		result = result * 22 + ( boardRight >> 30 & 0x1f );
	}else if( num == 6 ){
		result = boardLeft >> 11 & 0x1f;
		result = result * 22 + ( boardLeft >> 6 & 0x1f );
		result = result * 22 + ( boardLeft >> 1 & 0x1f );
		result = result * 22 + ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
		result = result * 22 + ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( boardRight >> 50 & 0x1f );
	}else if( num == 7 ){
		result = ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight & 0x1f );
		result = result * 22 + ( boardLeft >> 1 & 0x1f );
		result = result * 22 + ( boardRight >> 45 & 0x1f );
	}
	return result;
}

unsigned int GameBoardAI::getBox( int num )
{
	unsigned int result = 0;
	unsigned long long boardLeft = board_.get_left();
	unsigned long long boardRight = board_.get_right();
	if ( num == 0 ){
		result = ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( boardRight >> 50 & 0x1f );
		result = result * 22 + ( boardRight >> 45 & 0x1f );
		result = result * 22 + ( boardRight >> 35 & 0x1f );
		result = result * 22 + ( boardRight >> 30 & 0x1f );
		result = result * 22 + ( boardRight >> 25 & 0x1f );
	}else if ( num == 1 ){
		result = boardLeft >> 1 & 0x1f;
		result = result * 22 + ( boardRight >> 45 & 0x1f );
		result = result * 22 + ( boardRight >> 25 & 0x1f );
		result = result * 22 + ( boardLeft >> 6 & 0x1f );
		result = result * 22 + ( boardRight >> 50 & 0x1f );
		result = result * 22 + ( boardRight >> 30 & 0x1f );
	}else if( num == 2 ){
		result = boardRight >> 20 & 0x1f;
		result = result * 22 + ( boardRight >> 25 & 0x1f );
		result = result * 22 + ( boardRight >> 30 & 0x1f );
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( boardRight >> 45 & 0x1f );
		result = result * 22 + ( boardRight >> 50 & 0x1f );
	}else if( num == 3 ){
		result = boardRight >> 10 & 0x1f;
		result = result * 22 + ( boardRight >> 30 & 0x1f );
		result = result * 22 + ( boardRight >> 50 & 0x1f );
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( boardRight >> 25 & 0x1f );
		result = result * 22 + ( boardRight >> 45 & 0x1f );
	}else if( num == 4 ){
		result = ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( boardRight >> 45 & 0x1f );
		result = result * 22 + ( boardRight >> 50 & 0x1f );
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight >> 25 & 0x1f );
		result = result * 22 + ( boardRight >> 30 & 0x1f );
	}else if( num == 5 ){
		result = boardRight >> 25 & 0x1f;
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight  & 0x1f );
	}else if( num == 6 ){
		result = boardRight >> 5 & 0x1f;
		result = result * 22 + ( boardRight >> 25 & 0x1f );
		result = result * 22 + ( boardRight >> 45 & 0x1f );
		result = result * 22 + ( boardRight >> 10 & 0x1f );
		result = result * 22 + ( boardRight >> 30 & 0x1f );
		result = result * 22 + ( boardRight >> 50 & 0x1f );
	}else if( num == 7 ){
		result = boardRight >> 35 & 0x1f;
		result = result * 22 + ( boardRight >> 30 & 0x1f );
		result = result * 22 + ( boardRight >> 25 & 0x1f );
		result = result * 22 + ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( boardRight >> 50 & 0x1f );
		result = result * 22 + ( boardRight >> 45 & 0x1f );
	}
	return result;
}


unsigned int GameBoardAI::getBox2( int num )
{	
	unsigned int result = 0;
	unsigned long long boardLeft = board_.get_left();
	unsigned long long boardRight = board_.get_right();
	if ( num == 0 ){
		result = boardRight >> 45 & 0x1f;
		result = result * 22 + ( boardRight >> 25 & 0x1f );
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight & 0x1f );
	}else if ( num == 1 ){
		result = boardRight >> 25 & 0x1f;
		result = result * 22 + ( boardRight >> 30 & 0x1f );
		result = result * 22 + ( boardRight >> 35 & 0x1f );
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( boardRight >> 10 & 0x1f );
		result = result * 22 + ( boardRight >> 15 & 0x1f );
	}else if( num == 2 ){
		result = boardRight >> 30 & 0x1f;
		result = result * 22 + ( boardRight >> 50 & 0x1f );
		result = result * 22 + ( boardLeft >> 6 & 0x1f );
		result = result * 22 + ( boardRight >> 35 & 0x1f );
		result = result * 22 + ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( boardLeft >> 11 & 0x1f );
	}else if( num == 3 ){
		result = boardRight >> 50 & 0x1f;
		result = result * 22 + ( boardRight >> 45 & 0x1f );
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( boardLeft >> 6 & 0x1f );
		result = result * 22 + ( boardLeft >> 1 & 0x1f );
		result = result * 22 + ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
	}else if( num == 4 ){
		result = boardRight >> 50 & 0x1f;
		result = result * 22 + ( boardRight >> 30 & 0x1f );
		result = result * 22 + ( boardRight >> 10 & 0x1f );
		result = result * 22 + ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( boardRight >> 35 & 0x1f );
		result = result * 22 + ( boardRight >> 15 & 0x1f );
	}else if( num == 5 ){
		result = boardRight >> 45 & 0x1f;
		result = result * 22 + ( boardRight >> 50 & 0x1f );
		result = result * 22 + ( boardRight >> 55 & 0x1f );
		result = result * 22 + ( boardLeft >> 1 & 0x1f );
		result = result * 22 + ( boardLeft >> 6 & 0x1f );
		result = result * 22 + ( boardLeft >> 11 & 0x1f );
	}else if( num == 6 ){
		result = boardRight >> 25 & 0x1f;
		result = result * 22 + ( boardRight >> 45 & 0x1f );
		result = result * 22 + ( boardLeft >> 1 & 0x1f );
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight >> 40 & 0x1f );
		result = result * 22 + ( ( ( boardLeft & 0x1 ) << 4 ) | ( boardRight >> 60 & 0xf ) );
	}else if( num == 7 ){
		result = boardRight >> 30 & 0x1f;
		result = result * 22 + ( boardRight >> 25 & 0x1f );
		result = result * 22 + ( boardRight >> 20 & 0x1f );
		result = result * 22 + ( boardRight >> 10 & 0x1f );
		result = result * 22 + ( boardRight >> 5 & 0x1f );
		result = result * 22 + ( boardRight & 0x1f );
	}
	return result;
}

BitBoardAI GameBoardAI::restoreRow( BitBoardAI rowBits, int row )
{
  	return rowBits << (row * 20);
}



BitBoardAI GameBoardAI::restoreColumn( BitBoardAI columnBits, int column )
{
  	return ((columnBits & BitBoardAI(0xf8000)) << 45 |
            (columnBits & BitBoardAI(0x07c00)) << 30 |
            (columnBits & BitBoardAI(0x003e0)) << 15 |
            (columnBits & BitBoardAI(0x0001f)) ) << (column * 5);
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
