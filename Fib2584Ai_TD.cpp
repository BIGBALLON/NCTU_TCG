#include "Fib2584Ai_TD.h"
using namespace std;

TDLearning::TDLearning(bool trainMode, const std::string &filename)
:	filename(filename), 
	trainMode(trainMode)
{
	const int featureNum = 32 * 32 * 32 * 32;
	const long long featureNumAx = 23 * 23 * 23 * 23 * 23 * 23;
	ifstream fin(filename, ifstream::in | ifstream::binary);

	tableAx = new float[featureNumAx]; 
	tableInner = new float[featureNum]; 
	if (!fin.fail()) {
		fin.read((char *)tableAx, featureNumAx * sizeof(float));
		fin.read((char *)tableInner, featureNum * sizeof(float));
	}
	fin.close();
}

TDLearning::~TDLearning()
{
	const int featureNum = 32 * 32 * 32 * 32;
	const long long featureNumAx = 23 * 23 * 23 * 23 * 23 * 23;
	if (trainMode) {
		ofstream fout(filename, ifstream::out | ifstream::binary | ifstream::trunc);
		fout.write((char *)tableAx, featureNumAx * sizeof(float));
		fout.write((char *)tableInner, featureNum * sizeof(float));
		fout.close();
	}

	delete [] tableAx;
	delete [] tableInner;
}

void TDLearning::saveData()
{
	const int featureNum = 32 * 32 * 32 * 32;
	const long long featureNumAx = 23 * 23 * 23 * 23 * 23 * 23;
	if (trainMode) {
		ofstream fout(filename, ifstream::out | ifstream::binary | ifstream::trunc);

		fout.write((char *)tableAx, featureNumAx * sizeof(float));
		fout.write((char *)tableInner, featureNum * sizeof(float));
		fout.close();
	}
}


MoveDirection TDLearning::Move(const int board[4][4])
{
	GameBoardAI initBoard(board);
	MoveDirection bestDir;
	float bestValuePlusReward = NEGATIVE_INF;
	FeatureTable bestFeature;

	// Find the best direction to move
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
	const float alpha = 1;

	if (trainMode) {
		FeatureTable nextFeature;

		FeatureTable feature = record.top();
		record.pop();
		float delta = -getTableValue(feature);
		for (int i = 0; i < 8; i++) {
			tableAx[feature.ax[i]] += alpha * delta / SCALE;
		}
		for (int i = 0; i < 8; i++) {
			tableInner[feature.inner[i]] += alpha * delta / SCALE;
		}
		nextFeature = feature;

		while (!record.empty()) {
			FeatureTable feature = record.top();
			record.pop();

			float delta = getTableValue(nextFeature) + nextFeature.reward -
				getTableValue(feature);

			for (int i = 0; i < 8; i++) {
				tableAx[feature.ax[i]] += alpha * delta / SCALE;
			}
			for (int i = 0; i < 8; i++) {
				tableInner[feature.inner[i]] += alpha * delta / SCALE;
			}

			//tableEmpty[feature.emptyNum] += alpha * delta / SCALE;

			nextFeature = feature;
		}
	}
}

TDLearning::FeatureTable::FeatureTable(GameBoardAI &board, int reward)
:	reward(reward)
{

	inner[0] = (unsigned int)(board.getRow(1).get_right());
	inner[1] = (unsigned int)(board.getRow(2).get_right());
	inner[2] = (unsigned int)(board.getColumn(1).get_right());
	inner[3] = (unsigned int)(board.getColumn(2).get_right());
	inner[4] = reverseFeature(inner[0]);
	inner[5] = reverseFeature(inner[1]);
	inner[6] = reverseFeature(inner[2]);
	inner[7] = reverseFeature(inner[3]);
	ax[0] = board.getAx(0);
	ax[1] = board.getAx(1);
	ax[2] = board.getAx(2);
	ax[3] = board.getAx(3);
	ax[4] = board.getAx(4);
	ax[5] = board.getAx(5);
	ax[6] = board.getAx(6);
	ax[7] = board.getAx(7);

}

TDLearning::FeatureTable::FeatureTable(const FeatureTable &src)
:	reward(src.reward)
{
	for (int i = 0; i < 8; i++) {
		ax[i] = src.ax[i];
		inner[i] = src.inner[i];
	}
	emptyNum = src.emptyNum;
}

float TDLearning::getTableValue(const FeatureTable &feature) 
{
	float value = 0;

	for (int i = 0; i < 8; i++) {
		value += tableAx[feature.ax[i]];
	}
	for (int i = 0; i < 8; i++) {
		value += tableInner[feature.inner[i]];
	}

	value += feature.emptyNum;
	return value;
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
