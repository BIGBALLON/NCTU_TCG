#ifndef __FIB2584AI_TD_H__
#define __FIB2584AI_TD_H__


#include "GameBoardAI.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>
#include <fstream>
#include <iostream>
#include <climits>

class TDLearning
{
public:
	TDLearning(bool trainMode = true, const string &filename = string("table"));
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
		int emptyNum;
		int reward;	
	};

	const int SCALE = 100;	//  0.01

	string filename;
	stack<FeatureTable> record;
	bool trainMode;
	int *tableOuter;
	int *tableInner;
	int *tableEmpty;

	int getTableValue(const FeatureTable &feature) const;
	unsigned int reverseFeature(unsigned int a) const;
};

#endif