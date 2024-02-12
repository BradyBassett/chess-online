#include "Bitboard.h"

int Bitboard::getSquareNumber(Position position)
{
	return position.row * 8 + position.col;
}

Bitboard::Bitboard()
{
	// TODO - dynamically set bitboards based on fen position
	bitboards[0][0] = 0xff000000000000;	  // hexidecimal representation of white pawns in starting position
	bitboards[0][1] = 0x4200000000000000; // hexidecimal representation of white knights in starting position
	bitboards[0][2] = 0x2400000000000000; // hexidecimal representation of white bishops in starting position
	bitboards[0][3] = 0x8100000000000000; // hexidecimal representation of white rooks in starting position
	bitboards[0][4] = 0x800000000000000;  // hexidecimal representation of white queens in starting position
	bitboards[0][5] = 0x1000000000000000; // hexidecimal representation of white king in starting position

	bitboards[1][0] = 0xff00; // hexidecimal representation of black pawns in starting position
	bitboards[1][1] = 0x42;	  // hexidecimal representation of black knights in starting position
	bitboards[1][2] = 0x24;	  // hexidecimal representation of black bishops in starting position
	bitboards[1][3] = 0x81;	  // hexidecimal representation of black rooks in starting position
	bitboards[1][4] = 0x8;	  // hexidecimal representation of black queens in starting position
	bitboards[1][5] = 0x10;	  // hexidecimal representation of black king in starting position
}

uint64_t &Bitboard::getBitboard(Color color, PieceType pieceType)
{
	return bitboards[static_cast<int>(color)][static_cast<int>(pieceType)];
}

uint64_t Bitboard::getWhitePieces()
{
	return bitboards[0][0] | bitboards[0][1] | bitboards[0][2] | bitboards[0][3] | bitboards[0][4] | bitboards[0][5];
}

uint64_t Bitboard::getBlackPieces()
{
	return bitboards[1][0] | bitboards[1][1] | bitboards[1][2] | bitboards[1][3] | bitboards[1][4] | bitboards[1][5];
}

uint64_t Bitboard::getAllPieces()
{
	return getWhitePieces() | getBlackPieces();
}

void Bitboard::setBit(uint64_t &bitboard, Position position)
{
	auto x = 1ULL << getSquareNumber(position);
	bitboard |= 1ULL << getSquareNumber(position);
}

void Bitboard::clearBit(uint64_t &bitboard, Position position)
{
	auto x = 1ULL << getSquareNumber(position);
	bitboard ^= (1ULL << getSquareNumber(position));
}