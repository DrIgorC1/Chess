#include "BitBoard.h"

void Board_Print_Text(UINT64 arr[], const int size);

BitBoard::BitBoard()
{
	for (int i = 0; i < 12; i++)
	{
		if (i < 6)
		{
			bit_board[i].figure_and_color = (i + 1) | WHITE;
		}
		else
		{
			bit_board[i].figure_and_color = ((i + 1) - 6) | BLACK;
		}
	}
	init_coor_figure();
	init_all_bitboard();
	init_all_coor_bitboard();
	//init_knight_attacks();
	//init_lines_attacks();
}

BitBoard::BitBoard(const BitBoard& b)
{
	for (int i = 0; i < 12; i++)
	{
		this->bit_board[i] = b.bit_board[i];
	}
	init_all_bitboard();
	init_all_coor_bitboard();
	//init_knight_attacks();
	//init_lines_attacks(1);
}

BitBoard::~BitBoard()
{

}

void BitBoard::init_coor_figure()
{
	for (int i = 0; i < 12; i++)
	{
		switch (bit_board[i].figure_and_color)
		{
		case WHITE | PAWN:
			bit_board[i].coor = 65280;
			break;
		case WHITE | KNIGHT:
			bit_board[i].coor = 66;
			break;
		case WHITE | BISHOP:
			bit_board[i].coor = 36;
			break;
		case WHITE | ROOK:
			bit_board[i].coor = 129;
			break;
		case WHITE | QUEEN:
			bit_board[i].coor = 16;
			break;
		case WHITE | KING:
			bit_board[i].coor = 8;
			break;
		case BLACK | PAWN:
			bit_board[i].coor = 71776119061217280;
			break;
		case BLACK | KNIGHT:
			bit_board[i].coor = 4755801206503243776;
			break;
		case BLACK | BISHOP:
			bit_board[i].coor = 2594073385365405696;
			break;
		case BLACK | ROOK:
			bit_board[i].coor = 9295429630892703744;
			break;
		case BLACK | QUEEN:
			bit_board[i].coor = 1152921504606846976;
			break;
		case BLACK | KING:
			bit_board[i].coor = 576460752303423488;
			break;
		default:
			bit_board[i].coor = 1;
			break;
		}
	}
}

void BitBoard::init_all_bitboard()
{
	white_occupied = 0;
	black_occupied = 0;

	for (int i = 0; i < 6; i++)
	{
		white_occupied = white_occupied | bit_board[i].coor;
	}
	for (int i = 6; i < 12; i++)
	{
		black_occupied = black_occupied | bit_board[i].coor;
	}
}

void BitBoard::init_all_coor_bitboard()
{
	UINT64 all_coor[64] = {
		1, 2, 4, 8, 16, 32, 64, 128,
		256, 512, 1024, 2048, 4096, 8192, 16384, 32768,
		65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,
		16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648,
		4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888,
		1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328,
		281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968,
		72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808,
	};

}

void BitBoard::print_bitboard()
{
	all_occupied = white_occupied | black_occupied; // this black_occupied | white_occupied
	bool butboard[64];
	for (int i = 0; i < 64; i++)
	{
		butboard[i] = all_occupied % 2;
		all_occupied = all_occupied / 2;
	}
	for (int i = 64; i > 0; i--)
	{
		if ((i % 8 == 0) & (i >= 8))
		{
			std::cout << std::endl;
		}
		std::cout << butboard[i - 1];
	}
}

int BitBoard::set_figure_at(std::string movee)
{
	int a = (movee[1] - 49) * 8;
	int b = 'h' - movee[0];
	//UINT64 c = pow(2, (a + b));
	//white_occupied |= c;

	return a + b;
}

void BitBoard::init_figure_attacks()
{
	for (int i = 0; i < 12; i++)
	{
		switch (bit_board[i].figure_and_color)
		{
		case WHITE | PAWN:
			bit_board[i].coor = 65280;
			break;
		case WHITE | KNIGHT:
			init_knight_attacks();
			break;
		case WHITE | BISHOP:
			bit_board[i].coor = 36;
			break;
		case WHITE | ROOK:
			init_lines_attacks(2);
			break;
		case WHITE | QUEEN:
			init_lines_attacks(2);
			// init_diag_attacks()/////;
			break;
		case WHITE | KING:
			bit_board[i].coor = 8;
			break;
		case BLACK | PAWN:
			bit_board[i].coor = 71776119061217280;
			break;
		case BLACK | KNIGHT:
			init_knight_attacks();
			break;
		case BLACK | BISHOP:
			bit_board[i].coor = 2594073385365405696;
			break;
		case BLACK | ROOK:
			init_lines_attacks(2);
			break;
		case BLACK | QUEEN:
			init_lines_attacks(2);//!!!
			// init_diag_attacks()/////;
			break;
		case BLACK | KING:
			bit_board[i].coor = 576460752303423488;
			break;
		default:
			bit_board[i].coor = 1;
			break;
		}
	}
}

void BitBoard::init_knight_attacks()
{
	UINT64 knight_attacks[64] = { 132096, 329728, 659712, 1319424, 2638848, 5277696, 10489856, 4202496,
		33816580, 84410376, 168886289, 337772578, 675545156, 1351090312, 2685403152,
		8657044482, 21609056261, 43234889994, 86469779988, 172939559976, 345879119952, 687463207072,275414786112,
		2216203387392, 5531918402816, 11068131838464, 22136263676928, 44272527353856, 88545054707712, 175990581010432, 70506187341824,
		567348067172352, 1416171111120896, 2833441750646784, 5666883501293568, 11333767002587136, 22667534005174272, 45053588738670592,
		145241105196122112, 362539804446949376, 725361088165576704, 1450722176331153408, 2901444352662306816, 5802888705324613632, 11533718717099671552, 4620693356194824192,
		288234782788157440, 576469569871282176, 1224997833292120064, 2449995666584240128, 4899991333168480256, 9800114573372555264, 1152939715268182016, 2305878331024736256,
		1128098930098176, 2257297371824128, 4796069720358912, 9592139440717824, 19184278881435648, 38368557762871296, 4679521487814656, 9077567998918656
	};
	for (int i = 0; i < 64; i++)
	{
		bit_board[1].figure_move[i] = knight_attacks[i];
		bit_board[7].figure_move[i] = knight_attacks[i];
	}

	Board_Print_Text(knight_attacks, 64);
	//for (int i = 0; i < 64; i++)
	//	{
	//		white_occupied |= knight_attacks[i];
	//		white_occupied ^= knight_attacks[i];
	//		std::cout << std::endl << std::endl;
	//		std::cin.get();
	//	}
}

void BitBoard::init_lines_attacks(int k)
{
	UINT64 plus1[64] = {
		254, 252, 248, 240, 224, 192, 128, 0,
		65024, 64512, 63488, 61440, 57344, 49152, 32768, 0,
		16646144, 16515072, 16252928, 15728640, 14680064, 12582912, 8388608, 0 ,
		4261412864, 4227858432, 4160749568, 4026531840, 3758096384, 3221225472, 2147483648, 0,
		1090921693184, 1082331758592, 1065151889408, 1030792151040, 962072674304, 824633720832, 549755813888, 0,
		279275953455104, 277076930199552, 272678883688448, 263882790666240, 246290604621824, 211106232532992, 140737488355328, 0,
		71494644084506624, 70931694131085312, 69805794224242688, 67553994410557440, 63050394783186944, 54043195528445952, 36028797018963968, 0,
		18302628885633695744, 18158513697557839872, 17870283321406128128, 17293822569102704640, 16140901064495857664, 13835058055282163712, 9223372036854775808, 0
	};

	UINT64 minus1[64] = {
		0, 1, 3, 7, 15, 31, 63, 127,
		0, 256, 768, 1792, 3840, 7936, 16128, 32512,
		0, 65536, 196608, 458752, 983040, 2031616, 4128768, 8323072,
		0, 16777216, 50331648, 117440512, 251658240, 520093696, 1056964608, 2130706432,
		0, 4294967296, 12884901888, 30064771072, 64424509440, 133143986176, 270582939648, 545460846592,
		0, 1099511627776, 3298534883328, 7696581394432, 16492674416640, 34084860461056, 69269232549888, 139637976727552,
		0, 281474976710656, 844424930131968, 1970324836974592, 4222124650659840, 8725724278030336, 17732923532771328, 35747322042253312,
		0, 72057594037927936, 216172782113783808, 504403158265495552, 1080863910568919040, 2233785415175766016, 4539628424389459968, 9151314442816847872,
	};

	UINT64 plus8[64] = {
		72340172838076672, 144680345676153344, 289360691352306688, 578721382704613376, 1157442765409226752, 2314885530818453504, 4629771061636907008, 9259542123273814016,
		72340172838076416, 144680345676152832, 289360691352305664, 578721382704611328, 1157442765409222656, 2314885530818445312, 4629771061636890624, 9259542123273781248,
		72340172838010880, 144680345676021760, 289360691352043520, 578721382704087040, 1157442765408174080, 2314885530816348160, 4629771061632696320, 9259542123265392640,
		72340172821233664, 144680345642467328, 289360691284934656, 578721382569869312, 1157442765139738624, 2314885530279477248, 4629771060558954496, 9259542121117908992,
		72340168526266368, 144680337052532736, 289360674105065472, 578721348210130944, 1157442696420261888, 2314885392840523776, 4629770785681047552, 9259541571362095104,
		72339069014638592, 144678138029277184, 289356276058554368, 578712552117108736, 1157425104234217472, 2314850208468434944, 4629700416936869888, 9259400833873739776,
		72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	UINT64 minus8[64] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		1, 2, 4, 8, 16, 32, 64, 128,
		257, 514, 1028, 2056, 4112, 8224, 16448, 32896,
		65793, 131586, 263172, 526344, 1052688, 2105376, 4210752, 8421504,
		16843009, 33686018, 67372036, 134744072, 269488144, 538976288, 1077952576, 2155905152,
		4311810305, 8623620610, 17247241220, 34494482440, 68988964880, 137977929760, 275955859520, 551911719040,
		1103823438081, 2207646876162, 4415293752324, 8830587504648, 17661175009296, 35322350018592, 70644700037184, 141289400074368,
		282578800148737, 565157600297474, 1130315200594948, 2260630401189896, 4521260802379792, 9042521604759584, 18085043209519168, 36170086419038336,
	};

	UINT64 rook ;

	for (int j = 0; j < 64; j++)
	{
		UINT64 H6 = pow(2, 36);
		rook = (plus1[j] | minus1[j] | plus8[j] | minus8[j]);

		UINT64 blockers_figure = (plus1[j] | minus1[j] | plus8[j] | minus8[j]) & H6;
		if (blockers_figure != 0)
		{
			int counter = blockers(blockers_figure);
			rook = rook ^ plus8[counter];
		}

		rook = rook | H6;

		for (int i = 0; i < 64; i++)
		{
			std::cout << rook % 2;
			if ((i > 6) & ((i + 1) % 8 == 0))
			{
				std::cout << std::endl;
			}
			rook = rook / 2;
		}
		rook = 0;
		std::cout << std::endl << std::endl;
		std::cin.get();
	}
}
int BitBoard::blockers(UINT64 block)
{
	UINT64 blockers = block;
	for (int i = 0; i < 64; i++)
	{
		if (blockers % 2 != 0)
		{
			return i;
		}
		blockers /= 2;
	}
	return 0;
};

void Board_Print_Text(UINT64 arr[], const int size)
{
	for (int j = 0; j < 64; j++)
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[j] % 2;
			if ((i > 6) & (((i + 1) % 8) == 0))
			{
				std::cout << std::endl;
			}
			arr[j] = arr[j] / 2;
		}

		std::cout << std::endl << std::endl;
		std::cin.get();
	}
}

void BoardUnitTest_001()
{
	BitBoard b;
	b.init_lines_attacks(2);
	std::cin.get();
}

void BoardUnitTest_002()
{
	BitBoard b;
	b.init_knight_attacks();
	std::cin.get();

}

void BoardUnitTest_003()
{

	BitBoard b;
	UINT64 blockers;
	std::string move;
	int a;

	b.init_all_coor_bitboard();
	std::cin >> move;
	std::cout << std::endl;

	a = b.set_figure_at(move);
	UINT64 c = pow(2, a);
	std::cin.get();
	std::cout << std::endl;

	b.init_lines_attacks(a);


}

void BoardUnitTest()
{
	std::cout << "New" << std::endl;
	BoardUnitTest_001();

	std::cout << "Now knight_attacks" <<
		std::endl << std::endl;

	BoardUnitTest_002();
	//BoardUnitTest_003();
}