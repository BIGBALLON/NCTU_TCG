#include "BitBoardAI.h"

const BitBoardAI BitBoardAI::static_legal_mask = BitBoardAI(0xffff, 0xffffffffffffffff);

BitBoardAI::BitBoardAI():
left_(0),
right_(0)
{
}

BitBoardAI::BitBoardAI(unsigned long long right):
left_(0),
right_(right)
{
}

BitBoardAI::BitBoardAI(unsigned long long left, unsigned long long right):
left_(left),
right_(right)
{
	left_ &= static_legal_mask.left_; 
}

BitBoardAI::~BitBoardAI()
{
}

BitBoardAI::operator int()
{
	return right_;
}

BitBoardAI& BitBoardAI::operator=(const unsigned long long& right)
{
	left_ = 0;
	right_ = right;
	return *this;
}

bool BitBoardAI::operator==(const BitBoardAI& bit_board)
{
	return left_ == bit_board.left_ && right_ == bit_board.right_;
}

bool BitBoardAI::operator==(const int& right)
{
	return left_ == 0 && right_ == right;
}

bool BitBoardAI::operator!=(const BitBoardAI& bit_board)
{
	return left_ != bit_board.left_ || right_ != bit_board.right_;
}

bool BitBoardAI::operator!=(const int& right)
{
	return left_ != 0 || right_ != right;
}

BitBoardAI BitBoardAI::operator<<(const int& shift_num)
{
	if(shift_num == 0)
		return *this;
	BitBoardAI result = *this;
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

BitBoardAI& BitBoardAI::operator<<=(const int& shift_num)
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

BitBoardAI BitBoardAI::operator>>(const int& shift_num)
{
	if(shift_num == 0)
		return *this;
	BitBoardAI result = *this;
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

BitBoardAI& BitBoardAI::operator>>=(const int& shift_num)
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

BitBoardAI BitBoardAI::operator&(const BitBoardAI& bit_board) const
{
	return BitBoardAI(left_ & bit_board.left_, right_ & bit_board.right_);
}

BitBoardAI BitBoardAI::operator&(const int& right) const
{
	return BitBoardAI(left_ & 0, right_ & right);
}

BitBoardAI& BitBoardAI::operator&=(const BitBoardAI& bit_board)
{
	left_ &= bit_board.left_;
	right_ &= bit_board.right_;
	return *this;
}

BitBoardAI& BitBoardAI::operator&=(const int& right)
{
	left_ &= 0;
	right_ &= right;
	return *this;
}

BitBoardAI BitBoardAI::operator|(const BitBoardAI& bit_board)
{
	return BitBoardAI(left_ | bit_board.left_, right_ | bit_board.right_);
}

BitBoardAI& BitBoardAI::operator|=(const BitBoardAI& bit_board)
{
	left_ |= bit_board.left_;
	right_ |= bit_board.right_;
	return *this;
}

BitBoardAI BitBoardAI::operator~()
{
	return BitBoardAI(~left_, ~right_);
}

void BitBoardAI::show()
{
	cout << "left: " << hex << left_ << endl;
	cout << "right: " << hex << right_ << endl;
}
