#ifndef __MOVETABLE_H__
#define __MOVETABLE_H__

#include <cstdlib>
#include <cstring>

typedef unsigned int uint;

class MoveTable
{
public:
	static MoveTable move_table;

private:
	MoveTable();
	~MoveTable();
	void init_move_table();
	int move_row(uint& row, int start_pos, int end_pos, int direction, bool& movable);
	bool can_merge(uint row1, uint row2);
	int get_after_merge_tile(uint row1, uint row2);
	int get_tile(uint row);
	int get_fibonacci(int tile);

public:
	uint** row_move_table_;
	int** row_move_score_table_;
	bool** row_can_move_;
};

#endif