#pragma once
#include <cmath>
#include "Board.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#define U64 unsigned long long

static std::pair<U64, std::string> conformity[64] = {
	{1,"A8"}, {2,"B8"},{4,"C8"},{8,"D8"},{16,"E8"},{32,"F8"},{64,"G8"},{128,"H8"},
	{256,"A7"},{512,"B7"},{1024,"C7"},{2048,"D7"},{4096,"E7"},{8192,"F7"},{16384,"G7"},{32768,"H7"},
	{65536,"A6"},{131072,"B6"},{262144,"C6"},{524288,"D6"},{1048576,"E6"},{2097152,"F6"},{4194304,"G6"},{8388608,"H6"},
	{16777216,"A5"},{33554432,"B5"},{67108864,"C5"},{134217728,"D5"},{268435456,"E5"},{536870912,"F5"},{1073741824,"G5"},{2147483648,"H8"},
	{4294967296,"A4"}, {8589934592,"B4"}, {17179869184,"C4"}, {34359738368,"D4"}, {68719476736,"E4"}, {137438953472,"F4"}, {274877906944,"G4"}, {549755813888,"H4"},
	{1099511627776,"A3"}, {2199023255552,"B3"}, {4398046511104,"C3"}, {8796093022208,"D3"}, {17592186044416,"E3"}, {35184372088832,"F3"}, {70368744177664,"G3"}, {140737488355328,"H3"},
	{281474976710656,"A2"}, {562949953421312,"B2"}, {1125899906842624,"C2"}, {2251799813685248,"D2"},{4503599627370496,"E2"},{9007199254740992,"F2"},{18014398509481984,"G2"},{36028797018963968,"H2"},
	{72057594037927936,"A1"},{144115188075855872,"B1"}, {288230376151711744,"C1"}, {576460752303423488,"D1"}, {1152921504606846976,"E1"}, {2305843009213693952,"F1"}, {4611686018427387904,"G1"},{9223372036854775808,"H1"}
};

struct Struct_Bitboard
{
	short int figure_and_color;
	short int icoor;
	U64 ucoor = 0;
	U64 figure_move = 0;// Далее делаем массив ходов
	std::vector<std::string>  processed_move;
	int color;
};

class BitBoard : public Board
{
private:
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

	U64 white_occupied;
	U64 black_occupied;
	U64 all_occupied;

public:
	BitBoard();
	BitBoard(std::string fen) : Board(fen)
	{
		init_board();
		init_occupied();
		init_lines_move(2);
		conformityf(2);
	};
	void init_board();
	void init_occupied();

	U64 init_knight_move(int icoor);
	U64 init_diag_move(int icoor);
	U64 init_lines_move(int icoor);
	U64 init_king_move(int icoor);
	U64 init_whitepawn_move(int icoor);
	U64 init_blackpawn_move(int icoor);

	void generate();


	void conformityf(int icoor);
	void check_win();
	void print_bboard();

};
void BoardUnitTest();