#include "Fib2584Ai_TD.h"
using namespace std;

TDLearning::TDLearning(bool trainMode, const std::string &filename)
:	filename(filename), 
	trainMode(trainMode)
{
	const int featureNum = 32 * 32 * 32 * 32;
	ifstream fin(filename, ifstream::in | ifstream::binary);

	tableOuter = new int[featureNum]; 
	tableInner = new int[featureNum]; 
	if (!fin.fail()) {
		fin.read((char *)tableOuter, featureNum * sizeof(int));
		fin.read((char *)tableInner, featureNum * sizeof(int));
	}
}

TDLearning::~TDLearning()
{
	const int featureNum = 32 * 32 * 32 * 32;

	if (trainMode) {
		ofstream fout(filename, ifstream::out | ifstream::binary | ifstream::trunc);

		fout.write((char *)tableOuter, featureNum * sizeof(int));
		fout.write((char *)tableInner, featureNum * sizeof(int));
	}
	delete [] tableOuter;
	delete [] tableInner;
}

MoveDirection TDLearning::Move(const int board[4][4])
{
	GameBoardAI initBoard(board);
	MoveDirection bestDir;
	int bestValuePlusReward = INT_MIN;
	FeatureTable bestFeature;

	// Find the best direction to move
	for (int dir = 0; dir < 4; dir++) {
		GameBoardAI newBoard(initBoard);
		int reward = newBoard.move((MoveDirection)dir);
		if (newBoard == initBoard)
			continue;
		FeatureTable newFeature(newBoard, reward);
		int valuePlusReward = getTableValue(newFeature) + reward;
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
	const int alpha = 1;

	if (trainMode) {
		FeatureTable nextFeature;
		GameBoardAI endBoard(board);
		FeatureTable feature(endBoard, 0);
		int delta = -getTableValue(feature);
		
		for (int i = 0; i < 4; i++) {
			tableOuter[feature.outer[i]] += alpha * delta / SCALE;
			
			unsigned int rev = reverseFeature(feature.outer[i]);
			if (rev != feature.outer[i]) {
				tableOuter[rev] += alpha * delta / SCALE;
			}
		}
		for (int i = 0; i < 4; i++) {
			tableInner[feature.inner[i]] += alpha * delta / SCALE;
			
			unsigned int rev = reverseFeature(feature.inner[i]);
			if (rev != feature.inner[i]) {
				tableInner[rev] += alpha * delta / SCALE;
			}
		}
		nextFeature = feature;	

		while (!record.empty()) {
			FeatureTable feature = record.top();
			record.pop();

			int delta = getTableValue(nextFeature) + nextFeature.reward -
				getTableValue(feature);

			for (int i = 0; i < 4; i++) {
				tableOuter[feature.outer[i]] += alpha * delta / SCALE;
				
				unsigned int rev = reverseFeature(feature.outer[i]);
				if (rev != feature.outer[i]) {
					tableOuter[rev] += alpha * delta / SCALE;
				}
			}
			for (int i = 0; i < 4; i++) {
				tableInner[feature.inner[i]] += alpha * delta / SCALE;
				
				unsigned int rev = reverseFeature(feature.inner[i]);
				if (rev != feature.inner[i]) {
					tableInner[rev] += alpha * delta / SCALE;
				}
			}
			nextFeature = feature;
		}
	}
}

TDLearning::FeatureTable::FeatureTable(GameBoardAI &board, int reward)
:	reward(reward)
{
	outer[0] = (unsigned int)board.getRow(0);
	inner[0] = (unsigned int)board.getRow(1);
	inner[1] = (unsigned int)board.getRow(2);
	outer[1] = (unsigned int)board.getRow(3);
	outer[2] = (unsigned int)board.getColumn(0);
	inner[2] = (unsigned int)board.getColumn(1);
	inner[3] = (unsigned int)board.getColumn(2);
	outer[3] = (unsigned int)board.getColumn(3);
}

TDLearning::FeatureTable::FeatureTable(const FeatureTable &src)
:	reward(src.reward)
{
	for (int i = 0; i < 4; i++) {
		outer[i] = src.outer[i];
		inner[i] = src.inner[i];
	}
}

int TDLearning::getTableValue(const FeatureTable &feature) 
	const
{
	int value = 0;

	for (int i = 0; i < 4; i++) {
		value += tableOuter[feature.outer[i]];
	}
	for (int i = 0; i < 4; i++) {
		value += tableInner[feature.inner[i]];
	}

	return value;
}

unsigned int TDLearning::reverseFeature(unsigned int a) const
{
	unsigned int result = 0;

	for (int i = 0; i < 4; i++) {
		result = (result << 5) + (a & 0x1f);
		a >>= 5;
	}
	
	return result;
}
