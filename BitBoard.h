#pragma once
#include <cmath>
#include "Board.h"
#include <string>

#define UINT64 unsigned long long

class Board;


struct Struct_Bitboard
{
	int figure_and_color;
	UINT64 coor;
	UINT64 figure_move[64];// Далее делаем массив ходов
};

class BitBoard
{
private:

	Struct_Bitboard bit_board[12];
	UINT64 white_occupied;
	UINT64 black_occupied;
	UINT64 all_occupied;
	UINT64 all_coor[64];
	int state[64];

public:
	
	BitBoard();
	BitBoard(const BitBoard& B);
	~BitBoard();

	void init_coor_figure();
	void init_all_bitboard();
	void init_all_coor_bitboard();
	void print_bitboard();
	int set_figure_at(std::string movee);
	void init_figure_attacks();
	void init_knight_attacks();
	void init_lines_attacks(int a);
};

void BoardUnitTest();
