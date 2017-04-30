#include "MoveTable.h"

MoveTable MoveTable::move_table;

MoveTable::MoveTable()
{
	row_move_table_ = new uint*[2];
	row_move_score_table_ = new int*[2];
	row_can_move_ = new bool*[2];
	for(int i = 0;i < 2;i++) {
		row_move_table_[i] = new uint[0x100000];
		row_move_score_table_[i] = new int[0x100000];
		row_can_move_[i] = new bool[0x100000];
	}
	init_move_table();
}

MoveTable::~MoveTable()
{
	for(int i = 0;i < 2;i++) {
		delete[] row_move_table_[i];
		delete[] row_move_score_table_[i];
		delete[] row_can_move_[i];
	}
	delete[] row_move_table_;
	delete[] row_move_score_table_;
	delete[] row_can_move_;
}

void MoveTable::init_move_table()
{
	for(int i = 0;i < 0x100000;i++) {
		for(int direction = 0;direction <= 1;direction++) {
			uint row = i;
			bool movable = false;
			int score = move_row(row, 3 - direction * 3, 0 + direction * 3, direction, movable);
			row_move_table_[direction][i] = row;
			row_move_score_table_[direction][i] = score;
			row_can_move_[direction][i] = movable;
		}
	}
}

int MoveTable::move_row(uint& row, int start_pos, int end_pos, int direction, bool& movable)
{
	int score = 0;
	bool has_moved = false;
	uint tile_mask = 0x1f << (start_pos * 5);
	for(int i = start_pos;i != end_pos;i += direction?1:-1) {
		uint find_mask;
		int shift_count;
		if((row & tile_mask) == 0) {
			find_mask = direction?(tile_mask << 5):(tile_mask >> 5);
			shift_count = 1;
			while((row & find_mask) == 0) {
				find_mask = direction?((find_mask << 5) & 0xfffff):(find_mask >> 5);
				if(find_mask == 0)
					break;
				shift_count++;
			}
			if(find_mask != 0) {
				uint move_mask = direction?((row & find_mask) >> (5 * shift_count)):((row & find_mask) << (5 * shift_count));
				row &= ~find_mask;
				row |= move_mask;
				has_moved = true;
			}
			else
				break;
		}
		find_mask = direction?(tile_mask << 5):(tile_mask >> 5);
		uint find_tile_mask = direction?((row & tile_mask) << 5):((row & tile_mask) >> 5);
		shift_count = 1;
		while((row & find_mask) == 0) {
			find_mask = direction?((find_mask << 5) & 0xfffff):(find_mask >> 5);
			find_tile_mask = direction?((find_tile_mask << 5) & 0xfffff):(find_tile_mask >> 5);
			if(find_mask == 0)
				break;
			shift_count++;
		}
		if(find_mask == 0)
			break;
		if(can_merge(row & find_mask, find_tile_mask) == true) {
			int restore_tile_count = 0;
			uint new_tile = get_after_merge_tile(row & find_mask, find_tile_mask);
			while((find_tile_mask & 0x1f) == 0) {
				find_tile_mask >>= 5;
				restore_tile_count++;
			}
			find_tile_mask = new_tile;
			score += get_fibonacci(new_tile);
			find_tile_mask <<= restore_tile_count * 5;
			uint add_tile_mask = direction?(find_tile_mask >> (5 * shift_count)):(find_tile_mask << (5 * shift_count));
			row &= ~(find_mask | tile_mask);
			row |= add_tile_mask;
			has_moved = true;
		}
		tile_mask = direction?(tile_mask << 5):(tile_mask >> 5);
	}
	movable = has_moved;
	return score;
}

bool MoveTable::can_merge(uint row1, uint row2)
{
	int tile1 = get_tile(row1);
	int tile2 = get_tile(row2);
	if(tile1 == 0 || tile2 == 0)
		return false;
	if((tile1 == 1 && tile2 == 1) || abs(tile1 - tile2) == 1)
		return true;
	return false;
}

int MoveTable::get_after_merge_tile(uint row1, uint row2)
{
	int tile1 = get_tile(row1);
	int tile2 = get_tile(row2);
	if(tile1 > tile2)
		return tile1 + 1;
	return tile2 + 1;
}
	
int MoveTable::get_tile(uint row)
{
	for(int i = 0;i < 4;i++) {
		if(row & 0x1f)
			return row & 0x1f;
		row >>= 5;
	}
	return 0;
}

int MoveTable::get_fibonacci(int tile)
{
	static int fibonacci[32] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};
	return fibonacci[tile];
}

