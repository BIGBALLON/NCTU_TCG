#include <iostream>
#include <iomanip>
#include <string>
#include "Fib2584/MoveDirection.h"
//#include "Fib2584/Statistic.h"
#include "Fib2x3Solver.h"
using namespace std;



int main(int argc, char* argv[])
{
	// create and initialize solver
	Fib2x3Solver solver;
	// you may use any arguments you need (perhaps to load an external table?)
	solver.initialize(argc, argv);
	
	cout << "Initialization finished" << endl << endl;
	
	int counter = 1;
	// input problems
	while(1) {
		int arrayBoard[2][3];
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 3; j++) {
				int input;
				cin >> input;
				if(cin.fail()){
					cout << "Bye." << endl;
					return 0;
				}
				else
					arrayBoard[i][j] = input;
			}
		}

		double expectedScore = solver.evaluteExpectedScore(arrayBoard);
		int bestMove = solver.findBestMove(arrayBoard);
		
		string bestMoveDirection = "";
		switch(bestMove){
			case MOVE_UP:
				bestMoveDirection = "Up";
				break;
			case MOVE_RIGHT:
				bestMoveDirection = "Right";
				break;
			case MOVE_DOWN:
				bestMoveDirection = "Down";
				break;
			case MOVE_LEFT:
				bestMoveDirection = "Left";
				break;
			case CANNOT_MOVE:
				bestMoveDirection = "Cannot move";
				break;
			default:
				bestMoveDirection = "Invalid move number";
				break;
		}
		cout << "Problem " << counter << ": " << endl;	
		cout << "Best move: " << bestMoveDirection << endl;
		cout << "Expected score: " << setw(10) << setprecision(10) << expectedScore << endl << endl;
	}
	
	return 0;
}
