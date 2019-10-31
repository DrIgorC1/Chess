#pragma once
#include <iostream>
#include "BitBoard.h"

#define EMPTY 0 // 00 000 
#define PAWN 1 // 00 001
#define KNIGHT 2 // 00 010
#define BISHOP 3 // 00 011
#define ROOK 4 // 00 100
#define QUEEN 5 // 00 101
#define KING 6 // 00 110

#define WHITE 8 // 01 000
#define BLACK 16 // 10 000

#define COLOR_BITS 24 // 11 000
#define DIGNI_BITS 7 // 00 111

//struct Crdnts//coordinates 
//{
//	int x;
//	int y;
//	Crdnts(int _x, int _y) : x(_x), y(_y) {}
//};
//пока не нужны

class Board
{

private:
	std::string b_fen;
	int b_board[8][8];
	int b_move_number;//counter
	int b_move_color;

public:
	Board();
	Board(std::string fen);
	void PrintBoard();
	void Set_Figure_At(int figure,int x,int y);
	void Info_Digni(int x, int y);
	void Info_Color(int x, int y);
	void Init_board();
	void set_Figure_In(int x, int y, int counter);
};
