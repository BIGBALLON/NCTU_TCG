#include "BitBoard.h"

const BitBoard BitBoard::static_legal_mask = BitBoard(0xffff, 0xffffffffffffffff);

BitBoard::BitBoard():
left_(0),
right_(0)
{
}

BitBoard::BitBoard(unsigned long long right):
left_(0),
right_(right)
{
}

BitBoard::BitBoard(unsigned long long left, unsigned long long right):
left_(left),
right_(right)
{
	left_ &= static_legal_mask.left_; 
}

BitBoard::~BitBoard()
{
}

BitBoard::operator int()
{
	return right_;
}

BitBoard& BitBoard::operator=(const unsigned long long& right)
{
	left_ = 0;
	right_ = right;
	return *this;
}

bool BitBoard::operator==(const BitBoard& bit_board)
{
	return left_ == bit_board.left_ && right_ == bit_board.right_;
}

bool BitBoard::operator==(const int& right)
{
	return left_ == 0 && right_ == right;
}

bool BitBoard::operator!=(const BitBoard& bit_board)
{
	return left_ != bit_board.left_ || right_ != bit_board.right_;
}

bool BitBoard::operator!=(const int& right)
{
	return left_ != 0 || right_ != right;
}

BitBoard BitBoard::operator<<(const int& shift_num)
{
	if(shift_num == 0)
		return *this;
	BitBoard result = *this;
	if(shift_num < 64) {
		result.left_ <<= shift_num;
		result.left_ |= right_ >> (64 - shift_num);
		result.right_ <<= shift_num;
	}
	else {
		result.left_ = right_ << (shift_num - 64);
		result.right_ = 0;
	}
	result.left_ &= static_legal_mask.left_;
	return result;
}

BitBoard& BitBoard::operator<<=(const int& shift_num)
{
	if(shift_num == 0)
		return *this;
	if(shift_num < 64) {
		left_ <<= shift_num;
		left_ |= right_ >> (64 - shift_num);
		right_ <<= shift_num;
	}
	else {
		left_ = right_ << (shift_num - 64);
		right_ = 0;
	}
	left_ &= static_legal_mask.left_;
	return *this;
}

BitBoard BitBoard::operator>>(const int& shift_num)
{
	if(shift_num == 0)
		return *this;
	BitBoard result = *this;
	if(shift_num < 64) {
		result.right_ >>= shift_num;
		result.right_ |= left_ << (64 - shift_num);
		result.left_ >>= shift_num;
	}
	else {
		result.right_ = left_ >> (shift_num - 64);
		result.left_ = 0;
	}
	return result;
}

BitBoard& BitBoard::operator>>=(const int& shift_num)
{
	if(shift_num == 0)
		return *this;
	right_ >>= shift_num;
	if(shift_num < 64) {
		right_ |= left_ << (64 - shift_num);
		left_ >>= shift_num;
	}
	else {
		right_ = left_ >> (shift_num - 64);
		left_ = 0;
	}
	return *this;
}

BitBoard BitBoard::operator&(const BitBoard& bit_board) const
{
	return BitBoard(left_ & bit_board.left_, right_ & bit_board.right_);
}

BitBoard BitBoard::operator&(const int& right) const
{
	return BitBoard(left_ & 0, right_ & right);
}

BitBoard& BitBoard::operator&=(const BitBoard& bit_board)
{
	left_ &= bit_board.left_;
	right_ &= bit_board.right_;
	return *this;
}

BitBoard& BitBoard::operator&=(const int& right)
{
	left_ &= 0;
	right_ &= right;
	return *this;
}

BitBoard BitBoard::operator|(const BitBoard& bit_board)
{
	return BitBoard(left_ | bit_board.left_, right_ | bit_board.right_);
}

BitBoard& BitBoard::operator|=(const BitBoard& bit_board)
{
	left_ |= bit_board.left_;
	right_ |= bit_board.right_;
	return *this;
}

BitBoard BitBoard::operator~()
{
	return BitBoard(~left_, ~right_);
}

void BitBoard::show()
{
	cout << "left: " << hex << left_ << endl;
	cout << "right: " << hex << right_ << endl;
}
