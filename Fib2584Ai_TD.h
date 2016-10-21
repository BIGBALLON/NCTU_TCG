#ifndef __FIB2584AI_TD_H__
#define __FIB2584AI_TD_H__


#include "GameBoardAI.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>
#include <fstream>
#include <iostream>

#define NEGATIVE_INF -9999999
#define FEATURE_NUM 22
#define LINE_NUM 32

class TDLearning
{
public:
	TDLearning(bool trainMode = true, const string &filename = string("table"));
	~TDLearning();
	void saveData();
	MoveDirection Move(const int board[4][4]);
	void gameover(const int board[4][4]);

	float learningRate = 0.01;	
	bool maxTileFlag;
private:
	struct FeatureTable {
		FeatureTable() {}
		FeatureTable(GameBoardAI &board, int reward);
		FeatureTable(const FeatureTable &src);
		unsigned int reverseFeature(unsigned int a);

		unsigned int ax[8];
		unsigned int ax2[8];
		unsigned int box[8];
		unsigned int box2[8];
		unsigned int line[8];
		int reward;	
	};

	string filename;
	stack<FeatureTable> record;
	bool trainMode;
	float *tableAx;
	float *tableAx2;
	float *tableBox;
	float *tableBox2;
	float *tableLine;

	float getTableValue(const FeatureTable &feature);
};

#endif