#include "Fib2584Ai_TD.h"
using namespace std;

TDLearning::TDLearning(bool trainMode, const std::string &filename)
:	filename(filename), 
	trainMode(trainMode)
{
	const int featureNum = 32 * 32 * 32 * 32;
	const long long featureNumAx = 26 * 26 * 26 * 26 * 26 * 26;
	ifstream fin(filename, ifstream::in | ifstream::binary);

	tableAx = new int[featureNumAx]; 
	tableInner = new int[featureNum]; 
	if (!fin.fail()) {
		fin.read((char *)tableAx, featureNumAx * sizeof(int));
		fin.read((char *)tableInner, featureNum * sizeof(int));
	}
}

TDLearning::~TDLearning()
{
	const int featureNum = 32 * 32 * 32 * 32;
	const long long featureNumAx = 26 * 26 * 26 * 26 * 26 * 26;
	if (trainMode) {
		ofstream fout(filename, ifstream::out | ifstream::binary | ifstream::trunc);

		fout.write((char *)tableAx, featureNumAx * sizeof(int));
		fout.write((char *)tableInner, featureNum * sizeof(int));
	}
	delete [] tableAx;
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
			tableAx[feature.ax[i]] += alpha * delta / SCALE;
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
				tableAx[feature.ax[i]] += alpha * delta / SCALE;
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
	inner[0] = (unsigned int)board.getRow(1);
	inner[1] = (unsigned int)board.getRow(2);
	inner[2] = (unsigned int)board.getColumn(1);
	inner[3] = (unsigned int)board.getColumn(2);
	ax[0] = (unsigned int)board.getAx(0);
	ax[1] = (unsigned int)board.getAx(1);
	ax[2] = (unsigned int)board.getAx(2);
	ax[3] = (unsigned int)board.getAx(3);
}

TDLearning::FeatureTable::FeatureTable(const FeatureTable &src)
:	reward(src.reward)
{
	for (int i = 0; i < 4; i++) {
		ax[i] = src.ax[i];
		inner[i] = src.inner[i];
	}
}

int TDLearning::getTableValue(const FeatureTable &feature) 
	const
{
	int value = 0;

	for (int i = 0; i < 4; i++) {
		value += tableAx[feature.ax[i]];
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
