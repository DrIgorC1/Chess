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
	std::cout << b_fen << std::endl;
	init_board();
}

void Board::init_board()
{
	int c = 0;//counter
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (b_fen[c] > '0' && b_fen[c] < '9')
			{
				int temp = b_fen[c] - 48;
				for (int k = j; k < j + temp; k++)
				{
					b_board[i][k] = EMPTY;
				}
				j += temp - 1;
			}
			else
			{
				set_Figure_At(i, j, c);
			}
			c++;
		}
		c++;
	}

	if (b_fen[b_fen.size() - 5] == '-') //check for special pawn move
		b_two_field_move = false;
	else
		b_two_field_move = true;

	for (int j = 0; j < 4; j++) //set castling
	{
		switch (b_fen[b_fen.size() - 7 - j])
		{
		case 'q':
			*bk_pointer += CASTLING_0_0_;
			break;
		case 'k':
			*bk_pointer += CASTLING_0_0_0_;
			break;
		case 'Q':
			*wk_pointer += CASTLING_0_0_;
			break;
		case 'K':
			*wk_pointer += CASTLING_0_0_0_;
			break;
		default:
			break;
		}
	}

	b_move_color = (b_fen[c] == 'w') ? WHITE : BLACK;//set move's color
	b_move_number = b_fen[b_fen.size() - 1] - 48;//set move's number
	b_torm_pawn = b_fen[b_fen.size() - 3] - 48;//set the number of moves from the last move or taking a pawn
}

void Board::set_Figure_At(int x, int y, int counter)
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
		bk_pointer = &b_board[x][y];
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
		wk_pointer = &b_board[x][y];
		break;
	case 'P':
		b_board[x][y] = WHITE | PAWN;
		break;
	default:
		break;
	}
}

std::string Board::get_new_fen()
{
	b_fen = "";
	int c = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			switch (b_board[i][j] & DIGNI_COLOR)
			{
			case WHITE | PAWN:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'P';
				break;
			case WHITE | KNIGHT:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'N';
				break;
			case WHITE | BISHOP:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'B';
				break;
			case WHITE | ROOK:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'R';
				break;
			case WHITE | QUEEN:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'Q';
				break;
			case WHITE | KING:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'K';
				break;
			case BLACK | PAWN:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'p';
				break;
			case BLACK | KNIGHT:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'n';
				break;
			case BLACK | BISHOP:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'b';
				break;
			case BLACK | ROOK:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'r';
				break;
			case BLACK | QUEEN:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'q';
				break;
			case BLACK | KING:
				if (c != 0)
				{
					b_fen += c + 48;
					c = 0;
				}
				b_fen += 'k';
				break;
			case EMPTY:
				c++;
				break;
			default:
				break;
			}
		}
		if (c != 0)
		{
			b_fen += c + 48;
			c = 0;
		}
		if (i != 7)
			b_fen += '/';
	}
	
	b_fen += " ";
	b_move_color == WHITE ? b_fen += 'w' : b_fen += 'b';
	b_fen += " ";

	if ((*wk_pointer & CASTLING_0_0_0_) != 0) b_fen += "K";
	if ((*wk_pointer & CASTLING_0_0_) != 0) b_fen += "Q";
	if ((*bk_pointer & CASTLING_0_0_0_) != 0) b_fen += "k";
	if ((*bk_pointer & CASTLING_0_0_) != 0) b_fen += "q";

	b_fen += " ";
	if (b_two_field_move == true)  b_fen += 43; //Do not forget to change the number 43 to the coordinate
	else b_fen += 45;
	b_fen += " ";
	b_fen += b_torm_pawn + 48;
	b_fen += " ";
	b_fen += b_move_number + 48;
	

	/*std::cout << b_fen << std::endl;*/
	return b_fen;
}

void Board::print_board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << b_board[i][j];
		}
		std::cout << std::endl;
	}
}

void Board::set_fen(std::string fen)
{
	b_fen = fen;
	init_board();
}
