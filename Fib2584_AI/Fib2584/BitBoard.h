#ifndef __BITBOARD_H__
#define __BITBOARD_H__

#include <iostream>
using namespace std;

class BitBoard
{
private:
	static const BitBoard static_legal_mask;
public:
	BitBoard();
	BitBoard(unsigned long long right);
	BitBoard(unsigned long long left, unsigned long long right);
	~BitBoard();
	unsigned long long get_right() { return right_; };
	operator int();
	BitBoard& operator=(const unsigned long long& right);
	bool operator==(const BitBoard& bit_board);
	bool operator==(const int& right);
	bool operator!=(const BitBoard& bit_board);
	bool operator!=(const int& right);
	BitBoard operator<<(const int& shift_num);
	BitBoard& operator<<=(const int& shift_num);
	BitBoard operator>>(const int& shift_num);
	BitBoard& operator>>=(const int& shift_num);
	BitBoard operator&(const BitBoard& bit_board) const;
	BitBoard operator&(const int& right) const;
	BitBoard& operator&=(const BitBoard& bit_board);
	BitBoard& operator&=(const int& right);
	BitBoard operator|(const BitBoard& bit_board);
	BitBoard& operator|=(const BitBoard& bit_board);
	BitBoard operator~();
	void show();

private:
	unsigned long long left_;
	unsigned long long right_;
};

#endif