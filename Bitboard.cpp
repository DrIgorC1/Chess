#include "BitBoard.h"

BitBoard::BitBoard()
{

}

BitBoard::BitBoard(std::string fen) : b_fen(fen)
{
	init_board();
}

void BitBoard::init_board()
{
	int c = 0;//counter
	for (int j = 0; j < 64; j++)
	{
		if (b_fen[c] > '0' && b_fen[c] < '9')
		{
			j += b_fen[c] - '1';
		}
		else
		{
			set_icoor_figure(j,c);
		}
		c++;
	}
	color_move = b_fen[c];
}

void BitBoard::set_icoor_figure(int icoor, int counter)
{
	switch (b_fen[counter])
	{
	case 'r':
		init_black_rook(icoor);
		break;
	case 'b':
		init_black_bishop(icoor);
		break;
	case 'n':
		init_black_knight(icoor);
		break;
	case 'q':
		init_black_queen(icoor);
		break;
	case 'k':
		init_black_king(icoor);
		break;
	case 'p':
		init_black_pawn(icoor);
		break;
	case 'R':
		init_white_rook(icoor);
		break;
	case 'B':
		init_white_bishop(icoor);
		break;
	case 'N':
		init_white_knight(icoor);
		break;
	case 'Q':
		init_white_queen(icoor);
		break;
	case 'K':
		init_white_king(icoor);
		break;
	case 'P':
		init_white_pawn(icoor);
		break;
	default:
		break;
	}
}


void BitBoard::init_white_pawn(int coor)
{
	white_pawn.icoor = coor;			
	white_pawn.ucoor += pow(2, coor);
	//white_pawn.figure_move += init_pawn_move(white_pawn.icoor);
}

void BitBoard::init_white_knight(int coor)
{
	white_knight.icoor = coor;
	white_knight.ucoor += pow(2, coor);
	white_knight.figure_move += init_knight_move(white_knight.icoor);
}

void BitBoard::init_white_bishop(int coor)
{
	white_bishop.icoor = coor;
	white_bishop.ucoor += pow(2, coor);
	white_bishop.figure_move += init_diag_attacks(white_bishop.icoor);
}

void BitBoard::init_white_rook(int coor)
{
	white_rook.icoor = coor;
	white_rook.ucoor += pow(2, coor);
	white_rook.figure_move += init_lines_attacks(white_rook.icoor);
}

void BitBoard::init_white_queen(int coor)
{
	white_queen.icoor = coor;
	white_queen.ucoor += pow(2, coor);
	white_queen.figure_move += init_lines_attacks(white_queen.icoor);
	white_queen.figure_move += init_diag_attacks(white_queen.icoor);
}

void BitBoard::init_white_king(int coor)
{
	white_king.icoor = coor;
	white_king.ucoor += pow(2, coor);
	///white_king.figure_move += init_som
}

void BitBoard::init_black_pawn(int coor)
{
	black_pawn.icoor = coor;
	black_pawn.ucoor += pow(2, coor);
	black_pawn.figure_move += init_knight_move(black_pawn.icoor);
	////black_pawn.figure_move += init_pawn_move(black_pawn.icoor);
}

void BitBoard::init_black_knight(int coor)
{
	black_knight.icoor = coor;
	black_knight.ucoor += pow(2, coor);
	black_knight.figure_move += init_knight_move(black_knight.icoor);
}

void BitBoard::init_black_bishop(int coor)
{
	black_bishop.icoor = coor;
	black_bishop.ucoor += pow(2, coor);
	black_bishop.figure_move += init_diag_attacks(black_bishop.icoor);
}

void BitBoard::init_black_rook(int coor)
{
	black_rook.icoor = coor;
	black_rook.ucoor += pow(2, coor);
	black_rook.figure_move += init_lines_attacks(black_knight.icoor);
}

void BitBoard::init_black_queen(int coor)
{
	black_queen.icoor = coor;
	black_queen.ucoor += pow(2, coor);
	black_queen.figure_move += init_lines_attacks(black_queen.icoor);
	black_queen.figure_move += init_diag_attacks(black_queen.icoor);
}

void BitBoard::init_black_king(int coor)
{
	black_king.icoor = coor;
	black_king.ucoor += pow(2, coor);
	///black_king.figure_move += init_som
}

void BitBoard::processed_figure_move()
{
	static U64 all_coor[64] = {
		1, 2, 4, 8, 16, 32, 64, 128,
		256, 512, 1024, 2048, 4096, 8192, 16384, 32768,
		65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608,
		16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648,
		4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888,
		1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328,
		281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968,
		72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808,
	};

	for (int i = 0; i < 64; i++)
	{
		U64 temporary_variable_1 = all_coor[i] & white_knight.figure_move;
		U64 temporary_variable_2 = all_coor[i] & white_bishop.figure_move;
		U64 temporary_variable_3 = all_coor[i] & white_rook.figure_move;
		U64 temporary_variable_4 = all_coor[i] & white_queen.figure_move;
		U64 temporary_variable_5 = all_coor[i] & white_king.figure_move;
		U64 temporary_variable_6 = all_coor[i] & white_pawn.figure_move;

		U64 temporary_variable_11 = all_coor[i] & black_knight.figure_move;
		U64 temporary_variable_12 = all_coor[i] & black_bishop.figure_move;
		U64 temporary_variable_13 = all_coor[i] & black_rook.figure_move;
		U64 temporary_variable_14 = all_coor[i] & black_queen.figure_move;
		U64 temporary_variable_15 = all_coor[i] & black_king.figure_move;
		U64 temporary_variable_16 = all_coor[i] & black_pawn.figure_move;
		
		////generation of valid moves and attax form array
		////Then completely change

		if (temporary_variable_1 != 0)
		{
			white_knight.processed_move.push_back(i);
			attacks_from[white_knight.icoor] &= temporary_variable_1;
			attacks_to[i] &= white_knight.ucoor;
			white_bishop.processed_move.push_back(i);
			attacks_from[white_bishop.icoor] &= temporary_variable_2;
			attacks_to[i] &= white_bishop.ucoor;
			white_rook.processed_move.push_back(i);
			attacks_from[white_rook.icoor] &= temporary_variable_3;
			attacks_to[i] &= white_rook.ucoor;
			white_queen.processed_move.push_back(i);
			attacks_from[white_queen.icoor] &= temporary_variable_4;
			attacks_to[i] &= white_queen.ucoor;
			white_knight.processed_move.push_back(i);
			attacks_from[white_king.icoor] &= temporary_variable_5;
			attacks_to[i] &= white_king.ucoor;
			white_pawn.processed_move.push_back(i);
			attacks_from[white_pawn.icoor] &= temporary_variable_6;
			attacks_to[i] &= white_pawn.ucoor;

			black_knight.processed_move.push_back(i);
			attacks_from[black_knight.icoor] &= temporary_variable_11;
			attacks_to[i] &= black_knight.ucoor;
			black_bishop.processed_move.push_back(i);
			attacks_from[black_bishop.icoor] &= temporary_variable_12;
			attacks_to[i] &= black_bishop.ucoor;
			black_rook.processed_move.push_back(i);
			attacks_from[black_rook.icoor] &= temporary_variable_13;
			attacks_to[i] &= black_rook.ucoor;
			black_queen.processed_move.push_back(i);
			attacks_from[black_queen.icoor] &= temporary_variable_14;
			attacks_to[i] &= black_queen.ucoor;
			black_knight.processed_move.push_back(i);
			attacks_from[black_king.icoor] &= temporary_variable_15;
			attacks_to[i] &= black_king.ucoor;
			black_pawn.processed_move.push_back(i);
			attacks_from[black_pawn.icoor] &= temporary_variable_16;
			attacks_to[i] &= black_pawn.ucoor;

			temporary_variable_1 = 0;
			temporary_variable_2 = 0;
			temporary_variable_3 = 0;
			temporary_variable_4 = 0;
			temporary_variable_5 = 0;
			temporary_variable_6 = 0;
			temporary_variable_11 = 0;
			temporary_variable_12 = 0;
			temporary_variable_13 = 0;
			temporary_variable_14 = 0;
			temporary_variable_15 = 0;
			temporary_variable_16 = 0;
		}
	}

}

U64 BitBoard::blockers(U64 move_npr)
{
	for (int i = 0; i < 64; i++)
	{
		if (((move_npr) & all_occupied) != 0)
		{
			return i;
		}
	}
	return 0;
}

void BitBoard::init_attacks_to(int icoor, U64 move_legacy)
{
	attacks_to[icoor] = move_legacy;
}

void BitBoard::init_attacks_from(int icoor, U64 move_legacy)
{
	//////////сделать определение с единицами, где стоит фигура атакающая нас
}

void BitBoard::init_all_bitboard()
{
	white_occupied = white_pawn.ucoor | white_knight.ucoor |  white_bishop.ucoor 
		| white_rook.ucoor |  white_queen.ucoor |  white_king.ucoor;

	black_occupied = black_pawn.ucoor | black_knight.ucoor | black_bishop.ucoor
		| black_rook.ucoor | black_queen.ucoor | black_king.ucoor;

	all_occupied = white_occupied | black_occupied;
}

void BitBoard::init_all_coor_bitboard()
{
	static U64 all_coor[64] = {
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

U64 BitBoard::init_knight_move(int icoor)
{
	static U64 knight_attacks[64] = { 132096, 329728, 659712, 1319424, 2638848, 5277696, 10489856, 4202496,
		33816580, 84410376, 168886289, 337772578, 675545156, 1351090312, 2685403152,
		8657044482, 21609056261, 43234889994, 86469779988, 172939559976, 345879119952, 687463207072,275414786112,
		2216203387392, 5531918402816, 11068131838464, 22136263676928, 44272527353856, 88545054707712, 175990581010432, 70506187341824,
		567348067172352, 1416171111120896, 2833441750646784, 5666883501293568, 11333767002587136, 22667534005174272, 45053588738670592,
		145241105196122112, 362539804446949376, 725361088165576704, 1450722176331153408, 2901444352662306816, 5802888705324613632, 11533718717099671552, 4620693356194824192,
		288234782788157440, 576469569871282176, 1224997833292120064, 2449995666584240128, 4899991333168480256, 9800114573372555264, 1152939715268182016, 2305878331024736256,
		1128098930098176, 2257297371824128, 4796069720358912, 9592139440717824, 19184278881435648, 38368557762871296, 4679521487814656, 9077567998918656
	};

	U64 move_legacy;

	if ((color_move % 2) == 0)
	{
		move_legacy = (knight_attacks[icoor] | white_occupied) ^ black_occupied;
	}
	else
	{
		move_legacy = (knight_attacks[icoor] | black_occupied) ^ white_occupied;
	}

	return move_legacy;
}


U64 BitBoard::init_lines_attacks(int icoor)
{
	static U64 plus1[64] = {
		254, 252, 248, 240, 224, 192, 128, 0,
		65024, 64512, 63488, 61440, 57344, 49152, 32768, 0,
		16646144, 16515072, 16252928, 15728640, 14680064, 12582912, 8388608, 0 ,
		4261412864, 4227858432, 4160749568, 4026531840, 3758096384, 3221225472, 2147483648, 0,
		1090921693184, 1082331758592, 1065151889408, 1030792151040, 962072674304, 824633720832, 549755813888, 0,
		279275953455104, 277076930199552, 272678883688448, 263882790666240, 246290604621824, 211106232532992, 140737488355328, 0,
		71494644084506624, 70931694131085312, 69805794224242688, 67553994410557440, 63050394783186944, 54043195528445952, 36028797018963968, 0,
		18302628885633695744, 18158513697557839872, 17870283321406128128, 17293822569102704640, 16140901064495857664, 13835058055282163712, 9223372036854775808, 0
	};

	static U64 minus1[64] = {
		0, 1, 3, 7, 15, 31, 63, 127,
		0, 256, 768, 1792, 3840, 7936, 16128, 32512,
		0, 65536, 196608, 458752, 983040, 2031616, 4128768, 8323072,
		0, 16777216, 50331648, 117440512, 251658240, 520093696, 1056964608, 2130706432,
		0, 4294967296, 12884901888, 30064771072, 64424509440, 133143986176, 270582939648, 545460846592,
		0, 1099511627776, 3298534883328, 7696581394432, 16492674416640, 34084860461056, 69269232549888, 139637976727552,
		0, 281474976710656, 844424930131968, 1970324836974592, 4222124650659840, 8725724278030336, 17732923532771328, 35747322042253312,
		0, 72057594037927936, 216172782113783808, 504403158265495552, 1080863910568919040, 2233785415175766016, 4539628424389459968, 9151314442816847872,
	};

	static U64 plus8[64] = {
		72340172838076672, 144680345676153344, 289360691352306688, 578721382704613376, 1157442765409226752, 2314885530818453504, 4629771061636907008, 9259542123273814016,
		72340172838076416, 144680345676152832, 289360691352305664, 578721382704611328, 1157442765409222656, 2314885530818445312, 4629771061636890624, 9259542123273781248,
		72340172838010880, 144680345676021760, 289360691352043520, 578721382704087040, 1157442765408174080, 2314885530816348160, 4629771061632696320, 9259542123265392640,
		72340172821233664, 144680345642467328, 289360691284934656, 578721382569869312, 1157442765139738624, 2314885530279477248, 4629771060558954496, 9259542121117908992,
		72340168526266368, 144680337052532736, 289360674105065472, 578721348210130944, 1157442696420261888, 2314885392840523776, 4629770785681047552, 9259541571362095104,
		72339069014638592, 144678138029277184, 289356276058554368, 578712552117108736, 1157425104234217472, 2314850208468434944, 4629700416936869888, 9259400833873739776,
		72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808,
		0, 0, 0, 0, 0, 0, 0, 0,
	};

	static U64 minus8[64] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		1, 2, 4, 8, 16, 32, 64, 128,
		257, 514, 1028, 2056, 4112, 8224, 16448, 32896,
		65793, 131586, 263172, 526344, 1052688, 2105376, 4210752, 8421504,
		16843009, 33686018, 67372036, 134744072, 269488144, 538976288, 1077952576, 2155905152,
		4311810305, 8623620610, 17247241220, 34494482440, 68988964880, 137977929760, 275955859520, 551911719040,
		1103823438081, 2207646876162, 4415293752324, 8830587504648, 17661175009296, 35322350018592, 70644700037184, 141289400074368,
		282578800148737, 565157600297474, 1130315200594948, 2260630401189896, 4521260802379792, 9042521604759584, 18085043209519168, 36170086419038336,
	};

	U64 move_legacy;

	if ((color_move % 2) == 0)
	{
		U64 move_legacy = ((plus1[icoor] ^ blockers(plus1[icoor]) | minus1[icoor] ^ blockers(minus1[icoor]) |
			plus8[icoor] ^ blockers(plus8[icoor]) | minus8[icoor] ^ blockers(minus8[icoor]))
			| white_occupied) ^ (black_occupied);		 
	}
	else
	{
		U64 move_legacy = ((plus1[icoor] ^ blockers(plus1[icoor]) | minus1[icoor] ^ blockers(minus1[icoor]) |
			plus8[icoor] ^ blockers(plus8[icoor]) | minus8[icoor] ^ blockers(minus8[icoor]))
			| black_occupied) ^ (white_occupied);
	}

	U64 blockers;

	return move_legacy;
}
U64 BitBoard::init_diag_attacks(int icoor)
{
	static U64 plus9[64] = {
		9241421688590303744, 36099303471055872, 141012904183808, 550831656960, 2151686144, 8404992, 32768, 0,
		4620710844295151616, 9241421688590303232, 36099303471054848, 141012904181760, 550831652864, 2151677952, 8388608, 0,
		2310355422147510272,4620710844295020544,9241421688590041088,36099303470530560,275414777856,550829555712,2147483648,0,
		1155177711056977920,2310355422113955840,4620710844227911680,9241421688455823360,36099303202095104,141012366262272,549755813888,0,
		577588851233521664,1155177702467043328,2310355404934086656,4620710809868173312,9241421619736346624,36099165763141632,140737488355328,0,
		288793326105133056,577586652210266112,1155173304420532224,2310346608841064448,4620693217682128896,9241386435364257792,36028797018963968,0,
		144115188075855872, 288230376151711744, 576460752303423488, 1152921504606846976, 2305843009213693952, 4611686018427387904, 9223372036854775808,0,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	static U64 plus7[64] = {
		0,256,66048,16909312,4328785920,1108169199616,283691315109888,72624976668147712,
		0,8454144,2164391936,554084597760,141845657550848,36312488334065664,9295997013522907136,145249953336262656,
		0,16777216,4328521728,1108168671232,283691314053120,72624976666034176,145249953332068352,290499906664136704,
		0, 4294967296,1108101562368,283691179835392,72624976397598720,145249952795197440,290499905590394880,580999811180789760,
		0,1099511627776,283673999966208,72624942037860352,145249884075720704,290499768151441408,580999536302882816,1161999072605765632,
		0, 281474976710656,72620543991349248,145241087982698496,290482175965396992,580964351930793984,1161928703861587968,2323857407723175936,
		0,72057594037927936,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	static U64 minus9[64] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 1,2,4,8,16,32,64,
		0, 256,513,1026,2052,4104,8208,16416,
		0, 65536,131328,262657,525314,1050628,2101256,4202512,
		0, 16777216,33619968,67240192,134480385,268960770,537921540,1075843080,
		0, 4294967296,8606711808,17213489152,34426978560,68853957121,137707914242,275415828484,
		0, 1099511627776,2203318222848,4406653222912,8813306511360,17626613022976,35253226045953,70506452091906,
		0, 281474976710656,564049465049088,1128103225065472,2256206466908160,4512412933881856,9024825867763968,18049651735527937,
	};

	static U64 minus7[64] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		2,4,8,16,32,64,128,0,
		516,1032,2064,4128,8256,16512,32768,0,
		132104,264208,528416,1056832,2113664,4227072,8388608,0,
		33818640, 67637280,135274560,270549120,541097984,1082130432,2147483648,0,
		8657571872,17315143744,34630287488,69260574720,138521083904,277025390592,549755813888,0,
		2216338399296,4432676798592,8865353596928,17730707128320,35461397479424,70918499991552,140737488355328,0,
		567382630219904,1134765260439552,2269530520813568,4539061024849920,9078117754732544,18155135997837312,36028797018963968,0
	};

	U64 move_legacy;

	if ((color_move % 2) == 0)
	{
		U64 move_legacy = ((plus7[icoor] ^ blockers(plus7[icoor]) | minus7[icoor] ^ blockers(minus7[icoor]) |
			plus9[icoor] ^ blockers(plus9[icoor]) | minus9[icoor] ^ blockers(minus9[icoor]))
			| white_occupied) ^ (black_occupied);
	}
	else
	{
		U64 move_legacy = ((plus7[icoor] ^ blockers(plus7[icoor]) | minus7[icoor] ^ blockers(minus7[icoor]) |
			plus9[icoor] ^ blockers(plus9[icoor]) | minus9[icoor] ^ blockers(minus9[icoor]))
			| black_occupied) ^ (white_occupied);
	}

	return move_legacy;
}

void BitBoard::do_half_move()
{
	srand(time(NULL));

	int figure = rand() % 12;

	switch (figure)
	{
	case 1:
		int size = white_knight.processed_move.size();
		int random = rand() % size;
		white_knight.icoor = white_knight.processed_move[random];

		if ((white_knight.icoor & black_occupied) != 0)
		{
			black_occupied ^= white_knight.icoor;

			black_knight.icoor ^= white_knight.icoor;
			black_bishop.icoor ^= white_knight.icoor;
			black_rook.icoor ^= white_knight.icoor;
			black_queen.icoor ^= white_knight.icoor;
			black_king.icoor ^= white_knight.icoor; //?????
			black_pawn.icoor ^= white_knight.icoor;
		}
		break;
	case 2:
		int size = white_bishop.processed_move.size();
		int random = rand() % size;
		white_bishop.icoor = white_bishop.processed_move[random];
		break;
	case 3:
		int size = white_rook.processed_move.size();
		int random = rand() % size;
		white_rook.icoor = white_rook.processed_move[random];
		break;
	case 4:
		int size = white_queen.processed_move.size();
		int random = rand() % size;
		white_queen.icoor = white_queen.processed_move[random];
		break;
	case 5:
		int size = white_king.processed_move.size();
		int random = rand() % size;
		white_king.icoor = white_king.processed_move[random];
		break;
	case 6:
		int size = white_pawn.processed_move.size();
		int random = rand() % size;
		white_pawn.icoor = white_pawn.processed_move[random];
		break;
	case 7:
		int size = black_knight.processed_move.size();
		int random = rand() % size;
		black_knight.icoor = black_knight.processed_move[random];
		break;
	case 8:
		int size = black_bishop.processed_move.size();
		int random = rand() % size;
		black_bishop.icoor = black_bishop.processed_move[random];
		break;
	case 9:
		int size = black_rook.processed_move.size();
		int random = rand() % size;
		black_rook.icoor = black_rook.processed_move[random];
		break;
	case 10:
		int size = black_queen.processed_move.size();
		int random = rand() % size;
		black_queen.icoor = black_queen.processed_move[random];
		break;
	case 11:
		int size = black_king.processed_move.size();
		int random = rand() % size;
		black_king.icoor = black_king.processed_move[random];
		break;
	case 12:
		int size = black_pawn.processed_move.size();
		int random = rand() % size;
		black_pawn.icoor = black_pawn.processed_move[random];
		break;
	default:
		break;
	}
}

void BitBoard::read_fen()
{
	///
}

void BoardUnitTest_001()
{
}

void BoardUnitTest_003()
{

}

void BoardUnitTest()
{
	//BoardUnitTest_001();
	//BoardUnitTest_002();
	//BoardUnitTest_003();
}
