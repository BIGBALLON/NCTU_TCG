#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>
#include "Fib2584/MoveDirection.h"
#include "GameBoardAI.h"
using namespace std;

class Fib2584Ai
{
public:
	Fib2584Ai();
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
	MoveDirection generateMove(int board[4][4]);
	// do some action when game over
	void gameOver(int board[4][4], int iScore);

	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/

	class TDLearning
	{
	public:
		TDLearning(bool trainMode = true, 
			const string &filename = string("table"));
		~TDLearning();
		MoveDirection Move(const int board[4][4]);
		void gameover(const int board[4][4]);
	private:
		struct FeatureTable {
			FeatureTable() {}
			FeatureTable(GameBoardAI &board, int reward);
			FeatureTable(const FeatureTable &src);

			unsigned int outer[4];
			unsigned int inner[4];
			int reward;	
		};

		const int SCALE = 100;	//  0.01

		string filename;
		bool trainMode;
		int *tableOuter;
		int *tableInner;
		stack<FeatureTable> record;

		int getFeatureTableValue(const FeatureTable &feature) const;
		unsigned int reverseFeature(unsigned int a) const;
	};

	TDLearning td;
};

#endif