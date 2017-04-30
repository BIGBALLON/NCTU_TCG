#include "Fib2x3Solver.h"

Fib2x3Solver::Fib2x3Solver()
{	
    pos = new int[55555];
    for (int i = 0; i < 55555; ++i){
        pos[i] = -1;
    }
    pos[0] = 0;
    pos[1] = 1;
    pos[2] = 2;
    pos[3] = 3;
    pos[5] = 4;
    pos[8] = 5;
    pos[13] = 6;
    pos[21] = 7;
    pos[34] = 8;
    pos[55] = 9;
    pos[89] = 10;
    pos[144] = 11;
    pos[233] = 12;
    pos[377] = 13;
    pos[610] = 14;
}

void Fib2x3Solver::initialize(int argc, char* argv[])
{

    expect = new double[SIZE+2];
    bestMove = new int[SIZE+2];
    for( int i = 0; i < SIZE; ++i ){
        expect[i] = -1;
        bestMove[i] = -1;
    }

    int arr1[2][3] = {1, 1, 0, 0, 0, 0};
    int arr2[2][3] = {3, 1, 0, 0, 0, 0};
    int arr3[2][3] = {1, 3, 0, 0, 0, 0};
    int arr4[2][3] = {3, 3, 0, 0, 0, 0};

    int arr5[2][3] = {1, 0, 1, 0, 0, 0};
    int arr6[2][3] = {1, 0, 3, 0, 0, 0};
    int arr7[2][3] = {3, 0, 1, 0, 0, 0};
    int arr8[2][3] = {3, 0, 3, 0, 0, 0};

    int arr9[2][3] = {1, 0, 0, 1, 0, 0};
    int arr10[2][3] = {1, 0, 0, 3, 0, 0};
    int arr11[2][3] = {3, 0, 0, 1, 0, 0};
    int arr12[2][3] = {3, 0, 0, 3, 0, 0};

    int arr13[2][3] = {1, 0, 0, 0, 1, 0};
    int arr14[2][3] = {1, 0, 0, 0, 3, 0};
    int arr15[2][3] = {3, 0, 0, 0, 1, 0};
    int arr16[2][3] = {3, 0, 0, 0, 3, 0};

    int arr17[2][3] = {1, 0, 0, 0, 0, 1};
    int arr18[2][3] = {1, 0, 0, 0, 0, 3};
    int arr19[2][3] = {3, 0, 0, 0, 0, 1};
    int arr20[2][3] = {3, 0, 0, 0, 0, 3};

    int arr21[2][3] = {0, 1, 1, 0, 0, 0};
    int arr22[2][3] = {0, 1, 3, 0, 0, 0};
    int arr23[2][3] = {0, 3, 1, 0, 0, 0};
    int arr24[2][3] = {0, 3, 3, 0, 0, 0};


    int arr25[2][3] = {0, 1, 0, 1, 0, 0};
    int arr26[2][3] = {0, 1, 0, 3, 0, 0};
    int arr27[2][3] = {0, 3, 0, 1, 0, 0};
    int arr28[2][3] = {0, 3, 0, 3, 0, 0};

    int arr29[2][3] = {0, 1, 0, 0, 1, 0};
    int arr30[2][3] = {0, 1, 0, 0, 3, 0};
    int arr31[2][3] = {0, 3, 0, 0, 1, 0};
    int arr32[2][3] = {0, 3, 0, 0, 3, 0};

    int arr33[2][3] = {0, 1, 0, 0, 0, 1};
    int arr34[2][3] = {0, 1, 0, 0, 0, 3};
    int arr35[2][3] = {0, 3, 0, 0, 0, 1};
    int arr36[2][3] = {0, 3, 0, 0, 0, 3};

    int arr37[2][3] = {0, 0, 1, 1, 0, 0};
    int arr38[2][3] = {0, 0, 1, 3, 0, 0};
    int arr39[2][3] = {0, 0, 3, 1, 0, 0};
    int arr40[2][3] = {0, 0, 3, 3, 0, 0};

    int arr41[2][3] = {0, 0, 1, 0, 1, 0};
    int arr42[2][3] = {0, 0, 1, 0, 3, 0};
    int arr43[2][3] = {0, 0, 3, 0, 1, 0};
    int arr44[2][3] = {0, 0, 3, 0, 3, 0};

    int arr45[2][3] = {0, 0, 1, 0, 0, 1};
    int arr46[2][3] = {0, 0, 1, 0, 0, 3};
    int arr47[2][3] = {0, 0, 3, 0, 0, 1};
    int arr48[2][3] = {0, 0, 3, 0, 0, 3};

    int arr49[2][3] = {0, 0, 0, 1, 1, 0};
    int arr50[2][3] = {0, 0, 0, 1, 3, 0};
    int arr51[2][3] = {0, 0, 0, 3, 1, 0};
    int arr52[2][3] = {0, 0, 0, 3, 3, 0};

    int arr53[2][3] = {0, 0, 0, 1, 0, 1};
    int arr54[2][3] = {0, 0, 0, 1, 0, 3};
    int arr55[2][3] = {0, 0, 0, 3, 0, 1};
    int arr56[2][3] = {0, 0, 0, 3, 0, 3};

    int arr57[2][3] = {0, 0, 0, 0, 1, 1};
    int arr58[2][3] = {0, 0, 0, 0, 1, 3};
    int arr59[2][3] = {0, 0, 0, 0, 3, 1};
    int arr60[2][3] = {0, 0, 0, 0, 3, 3};

    dfs( arr1 );
    dfs( arr2 );
    dfs( arr3 );
    dfs( arr4 );
    dfs( arr5 );
    dfs( arr6 );
    dfs( arr7 );
    dfs( arr8 );
    dfs( arr9 );
    dfs( arr10 );
    dfs( arr11 );
    dfs( arr12 );
    dfs( arr13 );
    dfs( arr14 );
    dfs( arr15 );
    dfs( arr16 );
    dfs( arr17 );
    dfs( arr18 );
    dfs( arr19 );
    dfs( arr20 );
    dfs( arr21 );
    dfs( arr22 );
    dfs( arr23 );
    dfs( arr24 );
    dfs( arr25 );
    dfs( arr26 );
    dfs( arr27 );
    dfs( arr28 );
    dfs( arr29 );
    dfs( arr30 );
    dfs( arr31 );
    dfs( arr32 );
    dfs( arr33 );
    dfs( arr34 );
    dfs( arr35 );
    dfs( arr36 );
    dfs( arr37 );
    dfs( arr38 );
    dfs( arr39 );
    dfs( arr40 );
    dfs( arr41 );
    dfs( arr42 );
    dfs( arr43 );
    dfs( arr44 );
    dfs( arr45 );
    dfs( arr46 );
    dfs( arr47 );
    dfs( arr48 );
    dfs( arr49 );
    dfs( arr50 );
    dfs( arr51 );
    dfs( arr52 );
    dfs( arr53 );
    dfs( arr54 );
    dfs( arr55 );
    dfs( arr56 );
    dfs( arr57 );
    dfs( arr58 );
    dfs( arr59 );
    dfs( arr60 );
}

int Fib2x3Solver::check( int arr[2][3] ){
    int index = 0;
    for( int i = 0; i < 2; ++i ){
        for( int j = 0; j < 3; ++j ){
            if( pos[arr[i][j]] == -1 ){
                return 0;  
            } 
            index = index*14 + pos[arr[i][j]];
        }
    }
    if( expect[index] > -1 ) return index;
    else return 0;
}

int Fib2x3Solver::findBestMove(int arrayboard[2][3])
{
    int index = check(arrayboard);
    if( index ){
        return bestMove[index];
    }
    return -1;
}


double Fib2x3Solver::evaluteExpectedScore(int arrayboard[2][3])
{   
    int index = check(arrayboard);
    if( index ) return expect[index];
	else return -1;
}

int Fib2x3Solver::arr2index( int arr[2][3] ){
	int index = 0;
    for( int i = 0; i < 2; ++i ){
        for( int j = 0; j < 3; ++j ){
            index = index*14 + pos[arr[i][j]];
        }
    }
    return index;
}
// 0: up
// 1: right
// 2: down
// 3: left
// -1: cannot move

void Fib2x3Solver::printBoard( int arr[2][3] ){
    for( int i = 0; i < 2; ++i ){
        for( int j = 0; j < 3; ++j ){
            printf( "%d ", arr[i][j] );
        }
        puts("");
    }
        puts("");
}

void Fib2x3Solver::copyBoard( int arr[2][3], int tmp[2][3] ){
    for( int i = 0; i < 2; ++i ){
        for( int j = 0; j < 3; ++j ){
            tmp[i][j] = arr[i][j];
        }
    }
}

int Fib2x3Solver::cmparr( int arr[2][3], int tmp[2][3] ){
    for( int i = 0; i < 2; ++i ){
        for( int j = 0; j < 3; ++j ){
            if( arr[i][j] != tmp[i][j] )
                return 1;
        }
    }
    return 0;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/

double Fib2x3Solver::dfs( int arr[2][3] ){

    int tmp[2][3];
    int randomTileCnt = 0;
    double expectScore = 0.0;
    int score = 0.0;
    double bestScore = 0.0;
    int move = 4;
    int index = 0;
    for( int i = 0; i < 2; ++i ){
        for( int j = 0; j < 3; ++j ){
            index = index*14 + pos[arr[i][j]];
        }
    }
    if( expect[index] > -1 ) return expect[index];
    for( int i = 0; i < 4; ++i ){
        copyBoard( arr, tmp );
        //printBoard(tmp);
        if ( i == 0 ) score = up( tmp );
        else if ( i == 1 ) score = right( tmp );
        else if ( i == 2 ) score = down( tmp );
        else if ( i == 3 ) score = left( tmp );
        expectScore = score;
        if( cmparr( arr, tmp ) == 0 ) continue;
        randomTileCnt = 0;
        //printBoard(tmp);
        for (int r = 0; r < 2; ++r)
            for (int c = 0; c < 3; ++c)
                if ( tmp[r][c] == 0 ) randomTileCnt++;
        for (int r = 0; r < 2; ++r){            //row
            for (int c = 0; c < 3; ++c){        //col
                if ( tmp[r][c] != 0 ) continue;
                tmp[r][c] = 1;
                expectScore += 0.75*dfs( tmp )/randomTileCnt;
                tmp[r][c] = 3;
                expectScore += 0.25*dfs( tmp )/randomTileCnt;
                tmp[r][c] = 0;
            }
        }

        if( expectScore > bestScore ){
            bestScore = expectScore;
            move = i;
        }
    }
    bestMove[index] = move;
    return expect[index] = bestScore;
}

int Fib2x3Solver::down( int board[2][3] ){
    int score = 0;
    for( int i = 0; i < 3; ++i ){
        if ( board[0][i] && board[1][i] ){
            if ( ( board[0][i] == 1 && board[1][i] == 1 ) ||
                ( abs( pos[board[0][i]] - pos[board[1][i]] ) == 1 )
                ){
                board[1][i] += board[0][i];
                board[0][i] = 0;
                score += board[1][i];
            }
        }else if( board[1][i] ){

        }else if( board[0][i] ){
            board[1][i] = board[0][i];
            board[0][i] = 0;
        }
    }
    return score;
}

int Fib2x3Solver::up( int board[2][3] ){
    int score = 0;
    for( int i = 0; i < 3; ++i ){
        if ( board[0][i] && board[1][i] ){
            if ( ( board[0][i] == 1 && board[1][i] == 1 ) ||
                ( abs( pos[board[0][i]] - pos[board[1][i]] ) == 1 )
                ){
                board[0][i] += board[1][i];
                board[1][i] = 0;
                score += board[0][i];
            }
        }else if( board[0][i] ){

        }else if( board[1][i] ){
            board[0][i] = board[1][i];
            board[1][i] = 0;
        }
    }
    return score;
}

int Fib2x3Solver::right( int board[2][3] ){
    int score = 0;
    for( int i = 0; i < 2; ++i ){
        if( !board[i][0] && !board[i][1] && !board[i][2] ) continue;
        else if( !board[i][0] && !board[i][1] && board[i][2] ) continue;
        else if( !board[i][0] && board[i][1] && !board[i][2] ){
            board[i][2] = board[i][1];
            board[i][1] = 0;
        }
        else if( !board[i][0] && board[i][1] && board[i][2] ){
            if( abs( pos[board[i][1]] - pos[board[i][2]] ) == 1 || ( board[i][1] == 1 && board[i][2] == 1 ) ){
                board[i][2] += board[i][1];
                board[i][1] = 0;
                score += board[i][2];
            }
        }
        else if( board[i][0] && !board[i][1] && !board[i][2] ){
            board[i][2] = board[i][0];
            board[i][0] = 0;
        }
        else if( board[i][0] && !board[i][1] && board[i][2] ){
            if( abs( pos[board[i][0]] - pos[board[i][2]] ) == 1 || ( board[i][0] == 1 && board[i][2] == 1 ) ){
                board[i][2] += board[i][0];
                board[i][0] = 0;
                score += board[i][2];
            }else{
                board[i][1] = board[i][0];
                board[i][0] = 0;
            }
        }
        else if( board[i][0] && board[i][1] && !board[i][2] ){
            if( abs( pos[board[i][0]] - pos[board[i][1]] ) == 1 || ( board[i][0] == 1 && board[i][1] == 1 ) ){
                board[i][1] += board[i][0];
                board[i][2] = board[i][1];
                score += board[i][1];
                board[i][1] = 0;
                board[i][0] = 0;
            }else{
                board[i][2] = board[i][1];
                board[i][1] = board[i][0];
                board[i][0] = 0;
            }
        }
        else if( board[i][0] && board[i][1] && board[i][2] ){
            if( abs( pos[board[i][2]] - pos[board[i][1]] ) == 1 || ( board[i][2] == 1 && board[i][1] == 1 ) ){
                board[i][2] += board[i][1];
                board[i][1] = board[i][0];
                board[i][0] = 0;
                score += board[i][2];
            }
            else if( abs( pos[board[i][0]] - pos[board[i][1]] ) == 1 || ( board[i][0] == 1 && board[i][1] == 1 ) ){
                board[i][1] += board[i][0];
                board[i][0] = 0;
                score += board[i][1];
            }

        }
    }
    return score;
}


int Fib2x3Solver::left( int board[2][3] ){
    int score = 0;
    for( int i = 0; i < 2; ++i ){
        if( !board[i][0] && !board[i][1] && !board[i][2] ) continue;
        else if( !board[i][0] && !board[i][1] && board[i][2] ){
            board[i][0] = board[i][2];
            board[i][2] = 0;
        }
        else if( !board[i][0] && board[i][1] && !board[i][2] ){
            board[i][0] = board[i][1];
            board[i][1] = 0;
        }
        else if( !board[i][0] && board[i][1] && board[i][2] ){
            if( abs( pos[board[i][1]] - pos[board[i][2]] ) == 1 || ( board[i][1] == 1 && board[i][2] == 1 ) ){
                board[i][1] += board[i][2];
                score += board[i][1];
                board[i][0] = board[i][1];
                board[i][1] = 0;
                board[i][2] = 0;
            }else{
                board[i][0] = board[i][1];
                board[i][1] = board[i][2];
                board[i][2] = 0;
            }
        }
        else if( board[i][0] && !board[i][1] && !board[i][2] ) continue;
        else if( board[i][0] && !board[i][1] && board[i][2] ){
            if( abs( pos[board[i][0]] - pos[board[i][2]] ) == 1 || ( board[i][0] == 1 && board[i][2] == 1 ) ){
                board[i][0] += board[i][2];
                board[i][2] = 0;
                score += board[i][0];
            }else{
                board[i][1] = board[i][2];
                board[i][2] = 0;
            }
        }
        else if( board[i][0] && board[i][1] && !board[i][2] ){
            if( abs( pos[board[i][0]] - pos[board[i][1]] ) == 1 || ( board[i][0] == 1 && board[i][1] == 1 ) ){
                board[i][0] += board[i][1];
                score += board[i][0];
                board[i][1] = 0;
            }
        }
        else if( board[i][0] && board[i][1] && board[i][2] ){
            if( abs( pos[board[i][0]] - pos[board[i][1]] ) == 1 || ( board[i][0] == 1 && board[i][1] == 1 ) ){
                board[i][0] += board[i][1];
                score += board[i][0];
                board[i][1] = board[i][2];
                board[i][2] = 0;
            }
            else if( abs( pos[board[i][2]] - pos[board[i][1]] ) == 1 || ( board[i][2] == 1 && board[i][1] == 1 ) ){
                board[i][1] += board[i][2];
                board[i][2] = 0;
                score += board[i][1];
            }
        }
    }
    return score;
}
