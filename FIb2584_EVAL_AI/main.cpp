#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"
#include "Fib2584/Typedefs.h"
#include "Fib2584/Statistic.h"
#include "Fib2584Ai.h"
#include <stdio.h>
using namespace std;

int main(int argc, char* argv[])
{

//	freopen( "log.txt", "a", stdout );

	if(argc == 1) {
		cerr << "usage: play_game rounds [other arguments which your AI needs]" << endl;
		return 1;
	}
	int iPlayRounds = atoi(argv[1]);
	// create and initialize AI

	Fib2584Ai ai;
	ai.initialize(argc, argv);
	int cnt610, cnt1597, cnt2584, cnt4181, cnt6765, cnt10946, cnt17711, cnt28657, cnt46368;
	cnt610 = cnt1597 = cnt2584 = cnt4181 = cnt6765 = cnt10946 = cnt17711 = cnt28657 = cnt46368 = 0;
	// initialize statistic data
	Statistic statistic;
	statistic.setStartTime();
	// play each round

	int maxScore = 0;
	int maxTile = 0;
	for(int i = 0;i < iPlayRounds;i++) {
		GameBoard gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		while(!gameBoard.terminated()) {
			gameBoard.getArrayBoard(arrayBoard);
			MoveDirection moveDirection = ai.generateMove(arrayBoard);

			GameBoard originalBoard = gameBoard;
			iScore += gameBoard.move(moveDirection);
			if(originalBoard == gameBoard){
				continue;
			}
			statistic.increaseOneMove();

			//gameBoard.showBoard();
			gameBoard.addRandomTile();
			//gameBoard.showBoard();
		}
		gameBoard.getArrayBoard(arrayBoard);
		ai.gameOver(arrayBoard, iScore);
		statistic.increaseOneGame();

		statistic.updateScore(iScore);
		int maxTileTemp = gameBoard.getMaxTile();
		if ( maxTileTemp >= 610 ) cnt610++;
		if ( maxTileTemp >= 1597 ) cnt1597++;
		if ( maxTileTemp >= 2584 ) cnt2584++;
		if ( maxTileTemp >= 4181 ) cnt4181++;
		if ( maxTileTemp >= 6765 ) cnt6765++;
		if ( maxTileTemp >= 10946 ) cnt10946++;
		if ( maxTileTemp >= 17711 ) cnt17711++;
		if ( maxTileTemp >= 28657 ) cnt28657++;
		if ( maxTileTemp >= 46368 ) cnt46368++;

		if ( maxScore < iScore ){
			maxScore = iScore;
			
			if( maxTile < maxTileTemp ){
				maxTile = maxTileTemp;
			}
			printf("Games:%7d  maxScore = %6d  maxTile =  %5d", i, maxScore, maxTile );
			cout << endl;
		}

		statistic.updateMaxTile(gameBoard.getMaxTile());

		if ( i % 10000 == 0 && i != 0 ){
			printf("--------------------------------------------------------------\n");
			printf("-          One Line & Two Ax & Two Box & 610 limited         -\n");
			printf("-               learning rate:  %.5f                      -\n",ai.td.learningRate);
			printf("--------------------------------------------------------------\n");
			printf("Games:%7d\n", i );
			statistic.setFinishTime();
			statistic.show();
			statistic.reset();
			statistic.setStartTime();
			printf("--------------------------------------------------------------\n");
			printf("win rate 610: %f\n", float(cnt610)/100.0 );
			printf("win rate 1597: %f\n", float(cnt1597)/100.0 );
			printf("win rate 2584: %f\n", float(cnt2584)/100.0 );
			printf("win rate 6765: %f\n", float(cnt6765)/100.0 );
			printf("win rate 10946: %f\n", float(cnt10946)/100.0 );
			printf("win rate 17711: %f\n", float(cnt17711)/100.0 );
			printf("win rate 28657: %f\n", float(cnt28657)/100.0 );
			printf("win rate 46368: %f\n", float(cnt46368)/100.0 );
			printf("--------------------------------------------------------------\n");
			cnt610 = cnt1597 = cnt2584 = cnt4181 = cnt6765 = cnt10946 = cnt17711 = cnt28657 = cnt46368 = 0;
			cout << endl;
		}
		if( i % 70000 == 0 && i != 0 ){
			ai.td.saveData();
		}
	}
	statistic.setFinishTime();

	// output statistic data
	statistic.show();

	return 0;
}
