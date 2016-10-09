#include "Fib2584Ai.h"
#include <stdio.h>

#define ABS(x) ( (x) > 0 ? (x) : -(x) )
#define ROW 4
#define COL 4

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
	fibIndex = new int[2178310];
	fibIndex[0] = 0x3fffffff;
    fibIndex[1] = 1;
    fibIndex[2] = 2;
    fibIndex[3] = 3;
    fibIndex[5] = 4;
    fibIndex[8] = 5;
    fibIndex[13] = 6;
    fibIndex[21] = 7;
    fibIndex[34] = 8;
    fibIndex[55] = 9;
    fibIndex[89] = 10;
    fibIndex[144] = 11;
    fibIndex[233] = 12;
    fibIndex[377] = 13;
    fibIndex[610] = 14;
    fibIndex[987] = 15;
    fibIndex[1597] = 16;
    fibIndex[2584] = 17;
    fibIndex[4181] = 18;
    fibIndex[6765] = 19;
    fibIndex[10946] = 20;
    fibIndex[17711] = 21;
    fibIndex[28657] = 22;
    fibIndex[46368] = 23;
    fibIndex[75025] = 24;
    fibIndex[121393] = 25;
    fibIndex[196418] = 26;
    fibIndex[317811] = 27;
    fibIndex[514229] = 28;
    fibIndex[832040] = 29;
    fibIndex[1346269] = 30;
    fibIndex[2178309] = 31;
	return;
}



MoveDirection Fib2584Ai::generateMove(int board[4][4])
{

	MoveDirection select = static_cast<MoveDirection>(rand() % 4);

	int emptyCnt = getEmpty(board);

    int temp[4][4] = {0};	
	copyBoard(board,temp);
	int moveUp = moveOne(temp,MOVE_UP);

	copyBoard(board,temp);
	int moveDown = moveOne(temp,MOVE_DOWN);

	copyBoard(board,temp);
	int moveLeft = moveOne(temp,MOVE_LEFT);

	copyBoard(board,temp);
	int moveRight = moveOne(temp,MOVE_RIGHT);


	if (emptyCnt < moveUp ){
		emptyCnt = moveUp;
		select = MOVE_UP;
	}

	if (emptyCnt < moveDown ){
		emptyCnt = moveDown;
		select = MOVE_DOWN;
	}

	if (emptyCnt < moveLeft ){
		emptyCnt = moveLeft;
		select = MOVE_LEFT;
	}

	if (emptyCnt < moveRight ){
		emptyCnt = moveRight;
		select = MOVE_RIGHT;
	}

	return select;
}

int Fib2584Ai::moveOne( int board[4][4], MoveDirection iDirection )
{
    int temp[4][4] = {0};
	copyBoard(board,temp);
    switch (iDirection){
    case MOVE_UP:
        for(int row = 1; row < ROW; ++row)  {
            for(int crow = row; crow >= 1; --crow){
                for(int col = 0; col < COL; ++col){
                    if(board[crow-1][col] == 0){
                        board[crow-1][col] = board[crow][col];
                        board[crow][col] = 0;
                    }else {
                        if( ABS(fibIndex[board[crow-1][col]] - fibIndex[board[crow][col]]) == 1
                            || ( board[crow-1][col] == 1 && board[crow][col] == 1 )){
                            board[crow - 1][col] += board[crow][col];
                            board[crow][col] = 0;
                        }
                    }
                }
            }
        }
        break;
    case MOVE_DOWN:
        for(int row = ROW - 2; row >= 0; --row){
            for(int crow = row; crow < ROW - 1; ++crow){
                for(int col = 0; col < COL; ++col){
                    if(board[crow + 1][col] == 0){
                        board[crow + 1][col] = board[crow][col];
                        board[crow][col] = 0;
                    }else{
                         if( ABS(fibIndex[board[crow+1][col]] - fibIndex[board[crow][col]]) == 1
                            || ( board[crow+1][col] == 1 && board[crow][col] == 1 )){
                            board[crow + 1][col] += board[crow][col];
                            board[crow][col] = 0;
                        }
                    }
                }
            }
        }
        break;
    case MOVE_LEFT:
        for(int  col = 1; col < COL; ++col){
            for(int ccol = col; ccol >= 1; --ccol){
                for(int row = 0; row < ROW; ++row){
                    if(board[row][ccol-1] == 0){
                        board[row][ccol - 1] = board[row][ccol];
                        board[row][ccol] = 0;
                    }else{
                         if( ABS(fibIndex[board[row][ccol - 1]] - fibIndex[board[row][ccol]]) == 1
                            || ( board[row][ccol - 1] == 1 && board[row][ccol] == 1 ) ){
                            board[row][ccol - 1] += board[row][ccol];
                            board[row][ccol] = 0;
                        }
                    }
                }
            }
        }
        break;
    case MOVE_RIGHT:
        for(int  col = COL - 2; col >= 0; --col){
            for(int ccol = col; ccol <= COL - 2; ++ccol){
                for(int row = 0; row < ROW; ++row){
                    if(board[row][ccol + 1] == 0){
                        board[row][ccol + 1] = board[row][ccol];
                        board[row][ccol] = 0;
                    }else{
                        if( ABS(fibIndex[board[row][ccol + 1]] - fibIndex[board[row][ccol]]) == 1
                            || ( board[row][ccol + 1] == 1 && board[row][ccol] == 1 ) ){
                            board[row][ccol + 1] += board[row][ccol];
                            board[row][ccol] = 0;
                        }
                    }
                }
            }
        }
        break;
    }

    int isChanged = cmpBoard(board,temp);

    if (isChanged)
    	return getEmpty(board);
    return -1;

}


void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	return;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/

void Fib2584Ai::printBoard( int board[4][4] )
{
	for ( int i = 0; i < 4; ++i ){
		for( int j = 0; j < 4; ++j ){
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

bool Fib2584Ai::cmpBoard( int board[4][4], int temp[4][4] )
{
	for ( int i = 0; i < 4; ++i ){
		for( int j = 0; j < 4; ++j ){
			if( board[i][j] != temp[i][j] )
				return true;
		}
	}
	return false;
}

int Fib2584Ai::getEmpty( int board[4][4] )
{
	int cnt = 0;
	for ( int i = 0; i < 4; ++i ){
		for( int j = 0; j < 4; ++j ){
			if( board[i][j] == 0 )
				cnt++;
		}
	}
	return cnt;

}

void Fib2584Ai::copyBoard( int board[4][4], int temp[4][4] )
{
	for ( int i = 0; i < 4; i++ )
		for ( int j = 0; j < 4; j++ )
			temp[i][j] = board[i][j];

}