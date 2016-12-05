#include "Fib2584Ai_TD.h"
using namespace std;
const long long featureNum = FEATURE_NUM * FEATURE_NUM * FEATURE_NUM * FEATURE_NUM * FEATURE_NUM * FEATURE_NUM;
const int featureNumInner = LINE_NUM * LINE_NUM * LINE_NUM * LINE_NUM;



TDLearning::TDLearning(bool trainMode, const std::string &filename)
:	filename(filename), trainMode(trainMode)
{

	learningRate = 0.00001;	
	int playStep;
	int evilStep;
	maxTileFlag = false;
	ifstream fin(filename.c_str(), ifstream::in | ifstream::binary);

	tableAx = new float[featureNum]; 
	tableAx2 = new float[featureNum]; 
	tableBox = new float[featureNum]; 
	tableBox2 = new float[featureNum]; 
	tableLine = new float[featureNumInner]; 

	if (!fin.fail()) {
		fin.read((char *)tableAx, featureNum * sizeof(float));
		fin.read((char *)tableAx2, featureNum * sizeof(float));
		fin.read((char *)tableBox, featureNum * sizeof(float));
		fin.read((char *)tableBox2, featureNum * sizeof(float));
		fin.read((char *)tableLine, featureNumInner * sizeof(float));
	}
	fin.close();
}

TDLearning::~TDLearning()
{
	if (trainMode) {
		ofstream fout(filename.c_str(), ifstream::out | ifstream::binary | 
			ifstream::trunc);
		fout.write((char *)tableAx, featureNum * sizeof(float));
		fout.write((char *)tableAx2, featureNum * sizeof(float));
		fout.write((char *)tableBox, featureNum * sizeof(float));
		fout.write((char *)tableBox2, featureNum * sizeof(float));
		fout.write((char *)tableLine, featureNumInner * sizeof(float));
		fout.close();
	}

	delete [] tableAx;
	delete [] tableAx2;
	delete [] tableBox;
	delete [] tableBox2;
	delete [] tableLine;
}

void TDLearning::saveData()
{
	cout << "--------------------------------------------------------" << endl;
	if (trainMode) {
		ofstream fout(filename.c_str(), ifstream::out | ifstream::binary | ifstream::trunc);

		fout.write((char *)tableAx, featureNum * sizeof(float));
		fout.write((char *)tableAx2, featureNum * sizeof(float));
		fout.write((char *)tableBox, featureNum * sizeof(float));
		fout.write((char *)tableBox2, featureNum * sizeof(float));
		fout.write((char *)tableLine, featureNumInner * sizeof(float));
		fout.close();
	}

	cout << "-                   Table File Saved                   -" << endl;
	cout << "--------------------------------------------------------" << endl;
}

int TDLearning::generateEvilMove(const int board[4][4])
{
	

	int genTile = 1;
	if (evilStep >= 4){
		evilStep %= 4;
	}

	if ( evilStep == 3 ){
		genTile = 3;
	}

	float evilScote = 999999999;
	int boardTemp[4][4];
	MoveDirection bestDir;
	int bestI = 0;
	for (int i = 0; i < 16; ++i){
		if ( board[i/4][i%4] != 0 ) continue;
		memcpy(boardTemp,board,sizeof(boardTemp));
		boardTemp[i/4][i%4] = genTile;

		float bestValuePlusReward = -999999999;

		GameBoardAI initBoard(boardTemp);

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
			}
		}

		if ( evilScote > bestValuePlusReward ){
			evilScote = bestValuePlusReward;
			bestI = i;
		}
	}
	return bestI;
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
	playStep++;
	return bestDir;
}

void TDLearning::gameover(const int board[4][4])
{
	if (trainMode) {
		FeatureTable nextFeature;

		FeatureTable feature = record.top();
		record.pop();
		float delta = -getTableValue(feature);
		
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
				delta *= 5;
			}
		}
		
		float value = delta * learningRate;
		for (int i = 0; i < 8; i++) {
			tableAx[feature.ax[i]] += value;
			tableAx2[feature.ax2[i]] += value;
			tableBox[feature.box[i]] += value;
			tableBox2[feature.box2[i]] += value;
			tableLine[feature.line[i]] += value;
		}
		nextFeature = feature;

		while (!record.empty()) {
			FeatureTable feature = record.top();
			record.pop();
			float delta = getTableValue(nextFeature) + nextFeature.reward -	getTableValue(feature);
			float value = delta * learningRate;
			for (int i = 0; i < 8; i++) {
				tableAx[feature.ax[i]] += value;
				tableAx2[feature.ax2[i]] += value;
				tableBox[feature.box[i]] += value;
				tableBox2[feature.box2[i]] += value;
				tableLine[feature.line[i]] += value;
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
	line[0] = board.getLine(1);
	line[1] = board.getLine(2);
	line[2] = board.getLine(5);
	line[3] = board.getLine(6);
	line[4] = reverseFeature(line[0]);
	line[5] = reverseFeature(line[1]);
	line[6] = reverseFeature(line[2]);
	line[7] = reverseFeature(line[3]);

	for( int i = 0; i < 8; ++i ){
		ax[i] = board.getAx(i);
		ax2[i] = board.getAx2(i);
		box[i] = board.getBox(i);
		box2[i] = board.getBox2(i);
	}
}

TDLearning::FeatureTable::FeatureTable(const FeatureTable &src)
:	reward(src.reward)
{
	for (int i = 0; i < 8; i++) {
		ax[i] = src.ax[i];
		ax2[i] = src.ax2[i];
		box[i] = src.box[i];
		box2[i] = src.box2[i];
		line[i] = src.line[i];
	}
}

float TDLearning::getTableValue(const FeatureTable &feature) 
{
	float value = 0;

	for (int i = 0; i < 8; i++) {
		value += tableAx[feature.ax[i]];
		value += tableAx2[feature.ax2[i]];
		value += tableBox[feature.box[i]];
		value += tableBox2[feature.box2[i]];
		value += tableLine[feature.line[i]];
	}
	return value;
}

