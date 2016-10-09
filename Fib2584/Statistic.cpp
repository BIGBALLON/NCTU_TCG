#include "Statistic.h"

Statistic::Statistic()
{
	reset();
}

void Statistic::reset()
{
	iMaxTileOverall_ = 0;
	iWinGame_ = 0;
	iMaxScoreOverall_ = 0;
	iTotalScore_ = 0;
	iGameCount_ = 0;
	iMoveCount_ = 0;
	timeDifference_ = 0;
}

void Statistic::show()
{
	cout << "Win rate: " << iWinGame_ / (double)iGameCount_ * 100.0 << "%\n";
	cout << "Max score: " << iMaxScoreOverall_ << endl;
	cout << "Average score: " << iTotalScore_ / iGameCount_ << endl;
	cout << "Max tile: " << iMaxTileOverall_ << endl;
	double dTotalTime = timeDifference_ / (double)CLOCKS_PER_SEC;
	cout << dTotalTime / (double)iMoveCount_ << " sec/move" << endl;
	cout << iMoveCount_ / dTotalTime << " moves/sec" << endl;
}

void Statistic::increaseOneGame()
{
	iGameCount_++;
}

void Statistic::increaseOneMove()
{
	iMoveCount_++;
}

void Statistic::updateScore(int iScore)
{
	iTotalScore_ += iScore;
	iMaxScoreOverall_ = iScore > iMaxScoreOverall_?iScore:iMaxScoreOverall_;
}

void Statistic::updateMaxTile(int iTile)
{
	iWinGame_ += iTile >= 610?1:0;
	iMaxTileOverall_ = iTile > iMaxTileOverall_?iTile:iMaxTileOverall_;
}

void Statistic::setStartTime()
{
	timeDifference_ -= clock();
}

void Statistic::setFinishTime()
{
	timeDifference_ += clock();
}
