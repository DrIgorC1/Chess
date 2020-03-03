#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>

typedef short int CELL;

#define EMPTY 0    // 0000 0000 
#define PAWN 1     // 0000 0001
#define KNIGHT 2   // 0000 0010
#define BISHOP 3   // 0000 0011
#define ROOK 4     // 0000 0100
#define QUEEN 5    // 0000 0101
#define KING 6     // 0000 0110

#define WHITE 8    // 0000 1000
#define BLACK 16   // 0001 0000

#define MOVE 32    // 0010 0000

#define CASTLING_0_0_   64   // 0100 0000
#define CASTLING_0_0_0_ 128  // 1000 0000

#define COLOR_BITS 24        // 0001 1000
#define DIGNI_BITS 7         // 0000 0111
#define DIGNI_COLOR 31       // 0001 1111 

struct Crdnts//coordinates 
{
	int x;
	int y;
	/*Crdnts(int _x, int _y) : x(_x), y(_y) {}*/
};

class Board
{
protected:
	std::string b_fen;
	CELL b_board[8][8];
	int b_move_number;//counter
	int b_move_color;
	int b_torm_pawn;
	bool b_two_field_move;
	short int* wk_pointer;
	short int* bk_pointer;
	std::vector<Crdnts> move[8][8]; //this list of move
public:
	Board();
	Board(std::string fen);
	void init_board();
	void set_Figure_At(int x, int y, int counter);
	std::string get_new_fen();
	void print_board();
	void set_fen(std::string fen);
};