#include "Fib2584Ai_TD.h"
using namespace std;
const long long featureNum = FEATURE_NUM * FEATURE_NUM * FEATURE_NUM * FEATURE_NUM * FEATURE_NUM * FEATURE_NUM;
const int featureNumInner = LINE_NUM * LINE_NUM * LINE_NUM * LINE_NUM;

TDLearning::TDLearning(bool trainMode, const std::string &filename)
:	filename(filename), trainMode(trainMode)
{

	ifstream fin(filename, ifstream::in | ifstream::binary);
	ifstream fin2("A", ifstream::in | ifstream::binary);
	ifstream fin3("E", ifstream::in | ifstream::binary);

	
	tableAx = new float[featureNum]; 
	tableAx2 = new float[featureNum]; 
	tableBox = new float[featureNum]; 
	tableBox2 = new float[featureNum]; 
	tableLine = new float[featureNumInner]; 

	tableAxA = new float[featureNum]; 
	tableAx2A = new float[featureNum]; 
	tableBoxA = new float[featureNum]; 
	tableBox2A = new float[featureNum]; 
	tableLineA = new float[featureNumInner]; 

	tableAxE = new float[featureNum]; 
	tableAx2E = new float[featureNum]; 
	tableBoxE = new float[featureNum]; 
	tableBox2E = new float[featureNum]; 
	tableLineE = new float[featureNumInner]; 
	for (int i = 0; i < featureNum; ++i){
		tableAx[i] = 0.0;
		tableAx2[i] = 0.0;
		tableBox[i] = 0.0;
		tableBox2[i] = 0.0;
		tableAxA[i] = 0.0;
		tableAxE[i] = 0.0;
		tableAx2A[i] = 0.0;
		tableAx2E[i] = 0.0;
		tableBoxA[i] = 0.0;
		tableBoxE[i] = 0.0;
		tableBox2A[i] = 0.0;
		tableBox2E[i] = 0.0;
	}
	for (int i = 0; i < featureNumInner; ++i){
		tableLineA[i] = 0.0;
		tableLineE[i] = 0.0;
		tableLine[i] = 0.0;
	}

	if (!fin.fail()) {
		fin.read((char *)tableAx, featureNum * sizeof(float));
		fin.read((char *)tableAx2, featureNum * sizeof(float));
		fin.read((char *)tableBox, featureNum * sizeof(float));
		fin.read((char *)tableBox2, featureNum * sizeof(float));
		fin.read((char *)tableLine, featureNumInner * sizeof(float));
	}
	
	fin.close();

	if (!fin2.fail()) {
		fin2.read((char *)tableAxA, featureNum * sizeof(float));
		fin2.read((char *)tableAx2A, featureNum * sizeof(float));
		fin2.read((char *)tableBoxA, featureNum * sizeof(float));
		fin2.read((char *)tableBox2A, featureNum * sizeof(float));
		fin2.read((char *)tableLineA, featureNumInner * sizeof(float));
	}

	fin2.close();

	if (!fin3.fail()) {
		fin3.read((char *)tableAxE, featureNum * sizeof(float));
		fin3.read((char *)tableAx2E, featureNum * sizeof(float));
		fin3.read((char *)tableBoxE, featureNum * sizeof(float));
		fin3.read((char *)tableBox2E, featureNum * sizeof(float));
		fin3.read((char *)tableLineE, featureNumInner * sizeof(float));
	}

	fin3.close();
}
TDLearning::initialize()
{


}

TDLearning::~TDLearning()
{
	if (trainMode) {
		ofstream fout(filename, ifstream::out | ifstream::binary | ifstream::trunc);

		fout.write((char *)tableAx, featureNum * sizeof(float));
		fout.write((char *)tableAx2, featureNum * sizeof(float));
		fout.write((char *)tableBox, featureNum * sizeof(float));
		fout.write((char *)tableBox2, featureNum * sizeof(float));
		fout.write((char *)tableLine, featureNumInner * sizeof(float));
		fout.close();

		ofstream fout2("A", ifstream::out | ifstream::binary | ifstream::trunc);

		fout2.write((char *)tableAxA, featureNum * sizeof(float));
		fout2.write((char *)tableAx2A, featureNum * sizeof(float));
		fout2.write((char *)tableBoxA, featureNum * sizeof(float));
		fout2.write((char *)tableBox2A, featureNum * sizeof(float));
		fout2.write((char *)tableLineA, featureNumInner * sizeof(float));
		fout2.close();

		ofstream fout3("E", ifstream::out | ifstream::binary | ifstream::trunc);

		fout3.write((char *)tableAxE, featureNum * sizeof(float));
		fout3.write((char *)tableAx2E, featureNum * sizeof(float));
		fout3.write((char *)tableBoxE, featureNum * sizeof(float));
		fout3.write((char *)tableBox2E, featureNum * sizeof(float));
		fout3.write((char *)tableLineE, featureNumInner * sizeof(float));
		fout3.close();
	}

//important
	delete [] tableAx;
	delete [] tableAx2;
	delete [] tableBox;
	delete [] tableBox2;
	delete [] tableLine;
	delete [] tableAxA;
	delete [] tableAx2A;
	delete [] tableBoxA;
	delete [] tableBox2A;
	delete [] tableLineA;
	delete [] tableAxE;
	delete [] tableAx2E;
	delete [] tableBoxE;
	delete [] tableBox2E;
	delete [] tableLineE;
}

void TDLearning::saveData()
{
	cout << "--------------------------------------------------------" << endl;
	if (trainMode) {
		ofstream fout(filename, ifstream::out | ifstream::binary | ifstream::trunc);

		fout.write((char *)tableAx, featureNum * sizeof(float));
		fout.write((char *)tableAx2, featureNum * sizeof(float));
		fout.write((char *)tableBox, featureNum * sizeof(float));
		fout.write((char *)tableBox2, featureNum * sizeof(float));
		fout.write((char *)tableLine, featureNumInner * sizeof(float));
		fout.close();

		ofstream fout2("A", ifstream::out | ifstream::binary | ifstream::trunc);

		fout2.write((char *)tableAxA, featureNum * sizeof(float));
		fout2.write((char *)tableAx2A, featureNum * sizeof(float));
		fout2.write((char *)tableBoxA, featureNum * sizeof(float));
		fout2.write((char *)tableBox2A, featureNum * sizeof(float));
		fout2.write((char *)tableLineA, featureNumInner * sizeof(float));
		fout2.close();

		ofstream fout3("E", ifstream::out | ifstream::binary | ifstream::trunc);

		fout3.write((char *)tableAxE, featureNum * sizeof(float));
		fout3.write((char *)tableAx2E, featureNum * sizeof(float));
		fout3.write((char *)tableBoxE, featureNum * sizeof(float));
		fout3.write((char *)tableBox2E, featureNum * sizeof(float));
		fout3.write((char *)tableLineE, featureNumInner * sizeof(float));
		fout3.close();
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
		float value = delta * learningRate / 40.0, beta;
		for (int i = 0; i < 8; i++) {

			tableAxE[feature.ax[i]] += delta;
			tableAxA[feature.ax[i]] += fabs(delta);		
			if( tableAxA[feature.ax[i]] == 0 ){
				beta = 1.0;
			}else{
				/*printf("delta = %f\n", delta);
				printf("tableAxE[feature.ax[i]]=%f\ntableAxA[feature.ax[i]] = %f\n", tableAxE[feature.ax[i]],tableAxA[feature.ax[i]]);
				printf("beta1 = %f\n", beta);*/
				beta = fabs(tableAxE[feature.ax[i]])/tableAxA[feature.ax[i]];	
				//printf("beta2 = %f\n", beta);
				//system( "pause" );
			}
			/*printf("delta = %f\n", delta);
			printf("tableAxE[feature.ax[i]]=%f\ntableAxA[feature.ax[i]] = %f\n", tableAxE[feature.ax[i]],tableAxA[feature.ax[i]]);

			printf("beta = %f\n", beta);*/
			tableAx[feature.ax[i]] += value * beta;

			tableAx2E[feature.ax2[i]] += delta;
			tableAx2A[feature.ax2[i]] += fabs(delta);		

			if( tableAx2A[feature.ax2[i]] == 0 ){
				beta = 1.0;
			}else{
				beta = fabs(tableAx2E[feature.ax2[i]])/tableAx2A[feature.ax2[i]];
			}

			tableAx2[feature.ax2[i]] += value * beta;

			tableBoxE[feature.box[i]] += delta;
			tableBoxA[feature.box[i]] += fabs(delta);		
			if( tableBoxA[feature.box[i]] == 0 ){
				beta = 1.0;
			}else{
				beta = fabs(tableBoxE[feature.box[i]])/tableBoxA[feature.box[i]];
			}
			
			tableBox[feature.box[i]] += value * beta;

			tableBox2E[feature.box2[i]] += delta;
			tableBox2A[feature.box2[i]] += fabs(delta);	
			if( tableBox2A[feature.box2[i]] == 0 ){
				beta = 1.0;
			}else{
				beta = fabs(tableBox2E[feature.box2[i]])/tableBox2A[feature.box2[i]];
			}	
			
			tableBox2[feature.box2[i]] += value * beta;

			tableLineE[feature.line[i]] += delta;
			tableLineA[feature.line[i]] += fabs(delta);		
			if( tableLineA[feature.line[i]] == 0 ){
				beta = 1.0;
			}else{
				beta = fabs(tableLineE[feature.line[i]])/tableLineA[feature.line[i]];
			}
			
			tableLine[feature.line[i]] += value * beta;
		}
		nextFeature = feature;

		
		while (!record.empty()) {
			FeatureTable feature = record.top();
			record.pop();
			delta = getTableValue(nextFeature) + nextFeature.reward - getTableValue(feature);
			value = delta * learningRate / 40.0;
			for (int i = 0; i < 8; i++) {
	
				tableAxE[feature.ax[i]] += delta;
				tableAxA[feature.ax[i]] += fabs(delta);		
				if( tableAxA[feature.ax[i]] == 0 ){
					beta = 1.0;
				}else{
					/*printf("delta = %f\n", delta);
					printf("tableAxE[feature.ax[i]]=%f\ntableAxA[feature.ax[i]] = %f\n", tableAxE[feature.ax[i]],tableAxA[feature.ax[i]]);
					printf("beta1 = %f\n", beta);*/
					beta = fabs(tableAxE[feature.ax[i]])/tableAxA[feature.ax[i]];	
					//printf("beta2 = %f\n", beta);
					//system( "pause" );
				}
			
				
				tableAx[feature.ax[i]] += value * beta;

				tableAx2E[feature.ax2[i]] += delta;
				tableAx2A[feature.ax2[i]] += fabs(delta);		

				if( tableAx2A[feature.ax2[i]] == 0 ){
					beta = 1.0;
				}else{
					beta = fabs(tableAx2E[feature.ax2[i]])/tableAx2A[feature.ax2[i]];
				}

				tableAx2[feature.ax2[i]] += value * beta;

				tableBoxE[feature.box[i]] += delta;
				tableBoxA[feature.box[i]] += fabs(delta);		
				if( tableBoxA[feature.box[i]] == 0 ){
					beta = 1.0;
				}else{
					beta = fabs(tableBoxE[feature.box[i]])/tableBoxA[feature.box[i]];
				}
				
				tableBox[feature.box[i]] += value * beta;
	
				tableBox2E[feature.box2[i]] += delta;
				tableBox2A[feature.box2[i]] += fabs(delta);		
				if( tableBox2A[feature.box2[i]] == 0 ){
					beta = 1.0;
				}else{
					beta = fabs(tableBox2E[feature.box2[i]])/tableBox2A[feature.box2[i]];
				}	
				tableBox2[feature.box2[i]] += value * beta;
	
				tableLineE[feature.line[i]] += delta;
				tableLineA[feature.line[i]] += fabs(delta);		
				if( tableLineA[feature.line[i]] == 0 ){
					beta = 1.0;
				}else{
					beta = fabs(tableLineE[feature.line[i]])/tableLineA[feature.line[i]];
				}
				
				tableLine[feature.line[i]] += value * beta;
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

