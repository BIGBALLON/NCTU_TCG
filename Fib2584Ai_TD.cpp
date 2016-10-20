#include "Fib2584Ai_TD.h"
using namespace std;
const int featureNumInner = LINE_NUM * LINE_NUM * LINE_NUM * LINE_NUM;
const long long featureNumAx = BOX_NUM * BOX_NUM * BOX_NUM * BOX_NUM * BOX_NUM * BOX_NUM;
const long long featureNumBox = featureNumAx;

TDLearning::TDLearning(bool trainMode, const std::string &filename)
:	filename(filename), trainMode(trainMode)
{

	maxTileFlag = false;
	ifstream fin(filename, ifstream::in | ifstream::binary);

	tableAx = new float[featureNumAx]; 
	tableBox = new float[featureNumBox]; 
	tableBox2 = new float[featureNumBox]; 
	tableInner = new float[featureNumInner]; 

	if (!fin.fail()) {
		fin.read((char *)tableAx, featureNumAx * sizeof(float));
		fin.read((char *)tableBox, featureNumBox * sizeof(float));
		fin.read((char *)tableBox2, featureNumBox * sizeof(float));
		fin.read((char *)tableInner, featureNumInner * sizeof(float));
	}
	fin.close();
}

TDLearning::~TDLearning()
{
	if (trainMode) {
		ofstream fout(filename, ifstream::out | ifstream::binary | ifstream::trunc);
		fout.write((char *)tableAx, featureNumAx * sizeof(float));
		fout.write((char *)tableBox, featureNumBox * sizeof(float));
		fout.write((char *)tableBox2, featureNumBox * sizeof(float));
		fout.write((char *)tableInner, featureNumInner * sizeof(float));
		fout.close();
	}

	delete [] tableAx;
	delete [] tableBox;
	delete [] tableBox2;
	delete [] tableInner;
}

void TDLearning::saveData()
{
	cout << "--------------------------------------------------------" << endl;
	if (trainMode) {
		ofstream fout(filename, ifstream::out | ifstream::binary | ifstream::trunc);

		fout.write((char *)tableAx, featureNumAx * sizeof(float));
		fout.write((char *)tableBox, featureNumBox * sizeof(float));
		fout.write((char *)tableBox2, featureNumBox * sizeof(float));
		fout.write((char *)tableInner, featureNumInner * sizeof(float));
		fout.close();
	}

	cout << "-                   Table File Saved                   -" << endl;
	cout << "--------------------------------------------------------" << endl;
}


MoveDirection TDLearning::Move(const int board[4][4])
{
	GameBoardAI initBoard(board);
	MoveDirection bestDir;
	FeatureTable bestFeature;

	float bestValuePlusReward = NEGATIVE_INF;

	for (int dir = 0; dir < 4; dir++) {
		GameBoardAI newBoard(initBoard);
		int reward = newBoard.move((MoveDirection)dir);
		if (newBoard == initBoard)
			continue;
		FeatureTable newFeature(newBoard, reward);
		float valuePlusReward = getTableValue(newFeature) + reward;
		if (valuePlusReward > bestValuePlusReward) {
			bestDir = (MoveDirection)dir;
			bestValuePlusReward = valuePlusReward;
			bestFeature = newFeature;
		}
	}
	
	if (trainMode) {
		record.push(bestFeature);
	}

	return bestDir;
}

void TDLearning::gameover(const int board[4][4])
{
	if (trainMode) {
		FeatureTable nextFeature;

		FeatureTable feature = record.top();
		record.pop();
		float delta = -getTableValue(feature);
		/*
		if (maxTileFlag){
			int maxTile = 0;
			for (int i = 0; i < 4; ++i){
				for (int j = 0; j < 4; ++j){
					if( board[i][j] > maxTile ){
						maxTile = board[i][j];
					}
				}
			}
			if ( maxTile < 610 ){
				delta *= 15;
			}
		}
		*/
		for (int i = 0; i < 8; i++) {
			tableAx[feature.ax[i]] += delta * learningRate;
			tableBox[feature.box[i]] += delta * learningRate;
			tableBox2[feature.box2[i]] += delta * learningRate;
			tableInner[feature.inner[i]] += delta * learningRate;
		}
		nextFeature = feature;

		while (!record.empty()) {
			FeatureTable feature = record.top();
			record.pop();
			float delta = getTableValue(nextFeature) + nextFeature.reward -	getTableValue(feature);

			for (int i = 0; i < 8; i++) {
				tableAx[feature.ax[i]] += delta * learningRate;
				tableBox[feature.box[i]] += delta * learningRate;
				tableBox2[feature.box2[i]] += delta * learningRate;
				tableInner[feature.inner[i]] += delta * learningRate;
			}

			nextFeature = feature;
		}
	}
}

unsigned int TDLearning::FeatureTable::reverseFeature(unsigned int a)
{
	unsigned int result = 0;

	for (int i = 0; i < 4; i++) {
		result = (result << 5) + (a & 0x1f);
		a >>= 5;
	}
	return result;
}

TDLearning::FeatureTable::FeatureTable(GameBoardAI &board, int reward)
:	reward(reward)
{

	inner[0] = board.getLine(1);
	inner[1] = board.getLine(2);
	inner[2] = board.getLine(5);
	inner[3] = board.getLine(6);
	inner[4] = reverseFeature(inner[0]);
	inner[5] = reverseFeature(inner[1]);
	inner[6] = reverseFeature(inner[2]);
	inner[7] = reverseFeature(inner[3]);
	for( int i = 0; i < 8; ++i ){
		ax[i] = board.getAx(i);
		box[i] = board.getBox(i);
		box2[i] = board.getBox2(i);
	}
}

TDLearning::FeatureTable::FeatureTable(const FeatureTable &src)
:	reward(src.reward)
{
	for (int i = 0; i < 8; i++) {
		ax[i] = src.ax[i];
		inner[i] = src.inner[i];
		box[i] = src.box[i];
		box2[i] = src.box2[i];
	}
}

float TDLearning::getTableValue(const FeatureTable &feature) 
{
	float value = 0;

	for (int i = 0; i < 8; i++) {
		value += tableAx[feature.ax[i]];
		value += tableBox[feature.box[i]];
		value += tableBox2[feature.box2[i]];
		value += tableInner[feature.inner[i]];
	}
	return value;
}

