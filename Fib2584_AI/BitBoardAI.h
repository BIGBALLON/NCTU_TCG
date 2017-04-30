#ifndef __BITBOARDAI_H__
#define __BITBOARDAI_H__

#include <iostream>
using namespace std;

class BitBoardAI
{
private:
	static const BitBoardAI static_legal_mask;
public:
	BitBoardAI();
	BitBoardAI(unsigned long long right);
	BitBoardAI(unsigned long long left, unsigned long long right);
	~BitBoardAI();
	unsigned long long get_right() { return right_; };
	unsigned long long get_left() { return left_; };
	operator int();
	BitBoardAI& operator=(const unsigned long long& right);
	bool operator==(const BitBoardAI& bit_board);
	bool operator==(const int& right);
	bool operator!=(const BitBoardAI& bit_board);
	bool operator!=(const int& right);
	BitBoardAI operator<<(const int& shift_num);
	BitBoardAI& operator<<=(const int& shift_num);
	BitBoardAI operator>>(const int& shift_num);
	BitBoardAI& operator>>=(const int& shift_num);
	BitBoardAI operator&(const BitBoardAI& bit_board) const;
	BitBoardAI operator&(const int& right) const;
	BitBoardAI& operator&=(const BitBoardAI& bit_board);
	BitBoardAI& operator&=(const int& right);
	BitBoardAI operator|(const BitBoardAI& bit_board);
	BitBoardAI& operator|=(const BitBoardAI& bit_board);
	BitBoardAI operator~();
	void show();

private:
	unsigned long long left_;
	unsigned long long right_;
};

#endif