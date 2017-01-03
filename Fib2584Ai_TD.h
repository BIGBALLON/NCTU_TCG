#ifndef __FIB2584AI_TD_H__
#define __FIB2584AI_TD_H__


#include "GameBoardAI.h"

#include <cstdlib>
#include <ctime>
#include <string>
#include <stack>
#include <fstream>
#include <iostream>
#include <cmath>
#define NEGATIVE_INF -9999999
#define FEATURE_NUM 24
#define LINE_NUM 32

class TDLearning
{
public:
	TDLearning(bool trainMode = true, const string &filename = string("table"));
	~TDLearning();
	initialize();
	void saveData();
	MoveDirection Move(const int board[4][4]);
	void gameover(const int board[4][4]);

	float learningRate = 1.00;	
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

		unsigned int axE[8];
		unsigned int ax2E[8];
		unsigned int boxE[8];
		unsigned int box2E[8];
		unsigned int lineE[8];

		unsigned int axA[8];
		unsigned int ax2A[8];
		unsigned int boxA[8];
		unsigned int box2A[8];
		unsigned int lineA[8];
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

	float *tableAxA;
	float *tableAx2A;
	float *tableBoxA;
	float *tableBox2A;
	float *tableLineA;

	float *tableAxE;
	float *tableAx2E;
	float *tableBoxE;
	float *tableBox2E;
	float *tableLineE;

	float getTableValue(const FeatureTable &feature);
};

#endif