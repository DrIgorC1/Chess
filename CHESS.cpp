#include <iostream>
#include "Bitboard.h"

using namespace std;

int main()
{
    BitBoard b("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBN1 w KQkq - 0 1");
	cout << endl << endl;
	b.print_board();
	cout << endl << endl;
	b.print_bboard();
	cout << endl << endl;
	cout << b.get_new_fen();
	cout << endl << endl;
	b.set_fen("1k6/3q1n2/1q1nrnp1/8/2Q2N2/3R1R2/2K1N1N1/ w - -0 1");
	cout << b.get_new_fen();

    return 0;
}