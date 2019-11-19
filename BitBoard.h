#pragma once
#include <cmath>
#include "Board.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#define U64 unsigned long long

struct Struct_Bitboard
{
	/*	short int figure_and_color;*////Воазможно не нужно									
	short int icoor;
	U64 ucoor;
	U64 figure_move;// Далее делаем массив ходов
	std::vector<U64>  processed_move;
};

class BitBoard
{
private:
	Struct_Bitboard bit_board[12];///12 bitboard

	std::string b_fen;

	Struct_Bitboard white_pawn;
	Struct_Bitboard white_knight;
	Struct_Bitboard white_bishop;
	Struct_Bitboard white_rook;
	Struct_Bitboard white_queen;
	Struct_Bitboard white_king;

	Struct_Bitboard black_pawn;
	Struct_Bitboard black_knight;
	Struct_Bitboard black_bishop;
	Struct_Bitboard black_rook;
	Struct_Bitboard black_queen;
	Struct_Bitboard black_king;

	//static Struct_Bitboard all_bitboard[12] = { white_pawn, }//

	U64 white_occupied;
	U64 black_occupied;
	U64 all_occupied;

	U64 all_coor[64];
	int state[64];
	
	int color_move;

	U64 attacks_from[64];
	U64 attacks_to[64];

public:
	BitBoard();
	BitBoard(std::string fen);


	void init_board();
	void init_white_pawn(int coor);
	void init_white_knight(int coor);
	void init_white_bishop(int coor);
	void init_white_rook(int coor);
	void init_white_queen(int coor);
	void init_white_king(int coor);

	void init_black_pawn(int coor);
	void init_black_knight(int coor);
	void init_black_bishop(int coor);
	void init_black_rook(int coor);
	void init_black_queen(int coor);
	void init_black_king(int coor);

	void processed_figure_move();

	U64 blockers(U64 move_npr);
	void init_attacks_to(int icoor, U64 move_legacy);
	void init_attacks_from(int icoor, U64 move_legacy);


	void init_board();
	void set_icoor_figure(int icoor, int figure);
	void init_all_bitboard();///redact
	void init_all_coor_bitboard();
	U64 init_knight_move(int icoor);
	U64 init_lines_attacks(int icoor);
	U64 init_diag_attacks(int icoor);
	U64 init_king_attacks(int coor);
	/*void do_half_move();*/

};

void BoardUnitTest();