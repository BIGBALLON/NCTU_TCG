#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/Statistic.h"
#include "Fib2584Ai.h"
#include <stdio.h>
using namespace std;

int main(int argc, char* argv[])
{
	if(argc == 1) {
		cerr << "usage: play_game rounds [other arguments which your AI needs]" << endl;
		return 1;
	}
	int iPlayRounds = atoi(argv[1]);
	// create and initialize AI
	Fib2584Ai ai;
	ai.initialize(argc, argv);

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
			if(originalBoard == gameBoard)
				continue;
			statistic.increaseOneMove();

			gameBoard.addRandomTile();
		}
		gameBoard.getArrayBoard(arrayBoard);
		ai.gameOver(arrayBoard, iScore);
		statistic.increaseOneGame();

		statistic.updateScore(iScore);

		if ( maxScore < iScore ){
			maxScore = iScore;
			printf("Games:%7d  maxScore = %6d", i, maxScore );
			if ( maxTile < gameBoard.getMaxTile() ){
				maxTile = gameBoard.getMaxTile();
				printf("  maxTile =  %5d", maxTile );
			}
			cout << endl;
		}


		statistic.updateMaxTile(gameBoard.getMaxTile());

		if ( i % 10000 == 0 && i != 0 ){
			printf("--------------------------------------------------------------\n");
			printf("-          One Line & One Ax & One Box & 610 limited         -\n");
			printf("-               learning rate:  %.5f                      -\n",ai.td.learningRate);
			printf("--------------------------------------------------------------\n");
			printf("Games:%7d\n", i );
			statistic.setFinishTime();
			statistic.show();
			statistic.reset();
			statistic.setStartTime();
			printf("--------------------------------------------------------------\n");
			cout << endl;
		}
		if( i % 50000 == 0 && i != 0 ){
			ai.td.saveData();
		}
	}
	statistic.setFinishTime();

	// output statistic data
	statistic.show();

	return 0;
}