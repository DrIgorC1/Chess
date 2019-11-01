#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			b_board[i][j] = EMPTY;
		}
	}
	b_move_number = 0;
}

Board::Board(std::string fen) : b_fen(fen)
{
	Init_board();
}

void Board::Init_board()
{
	int c = 0;//counter
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (b_fen[c] > '0' && b_fen[c] < '9')
			{
				int temp = b_fen[c] - 48;
				for (int k = 0; k < temp; k++)
				{
					b_board[i][j] = EMPTY;
					j++;
				}
			}
			else
			{
				set_Figure_In(i, j, c);

			}
			c++;
		}
		c++;
	}
	b_move_color = (b_fen[c] == 'w') ? WHITE : BLACK;//set move's color
	b_move_number = b_fen[b_fen.size() - 1] - 48;
}

void Board::set_Figure_In(int x, int y, int counter)
{
	switch (b_fen[counter])
	{
	case 'r':
		b_board[x][y] = BLACK | ROOK;
		break;
	case 'b':
		b_board[x][y] = BLACK | BISHOP;
		break;
	case 'n':
		b_board[x][y] = BLACK | KNIGHT;
		break;
	case 'q':
		b_board[x][y] = BLACK | QUEEN;
		break;
	case 'k':
		b_board[x][y] = BLACK | KING;
		break;
	case 'p':
		b_board[x][y] = BLACK | PAWN;
		break;
	case 'R':
		b_board[x][y] = WHITE | ROOK;
		break;
	case 'B':
		b_board[x][y] = WHITE | BISHOP;
		break;
	case 'N':
		b_board[x][y] = WHITE | KNIGHT;
		break;
	case 'Q':
		b_board[x][y] = WHITE | QUEEN;
		break;
	case 'K':
		b_board[x][y] = WHITE | KING;
		break;
	case 'P':
		b_board[x][y] = WHITE | PAWN;
		break;
	default:
		break;
	}
}

void Board::PrintBoard()
{
	system("cls");

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((b_board[i][j] == 9) | (b_board[i][j] == 0) )
			{
				std::cout << b_board[i][j] << "  ";
			}
			else
			std::cout << b_board[i][j] << " " ;
		}
		std::cout << std::endl;
	}
}

void Board::Set_Figure_At(int figure,int x,int y)
{

	b_board[x][y] = figure;
}

void Board::Info_Color(int x, int y)
{
	std::cout << "Цвет фигуры на поле с координатам x = " << x << " y = " << y << " - "
		<< (b_board[x][y] & COLOR_BITS) << std::endl;
}

void Board::Info_Digni(int x, int y)
{
	std::cout << "Фигура на поле с координатам x = " << x << " y = " << y << " - "
		<< (b_board[x][y] & DIGNI_BITS) << std::endl;
}
