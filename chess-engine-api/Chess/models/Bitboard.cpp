#include "Bitboard.h"

int Bitboard::getSquareNumber(Position position)
{
	return position.row * 8 + position.col;
}

Bitboard::Bitboard()
{
	whitePawns = 0xff000000000000;	   // hexidecimal representation of pa whitewns in starting position
	whiteKnights = 0x4200000000000000; // hexidecimal representation of white knights in starting position
	whiteBishops = 0x2400000000000000; // hexidecimal representation of white bishops in starting position
	whiteRooks = 0x8100000000000000;   // hexidecimal representation of white rooks in starting position
	whiteQueens = 0x800000000000000;   // hexidecimal representation of white queens in starting position
	whiteKing = 0x1000000000000000;	   // hexidecimal representation of white king in starting position

	blackPawns = 0xff00; // hexidecimal representation of black pawns in starting position
	blackKnights = 0x42; // hexidecimal representation of black knights in starting position
	blackBishops = 0x24; // hexidecimal representation of black bishops in starting position
	blackRooks = 0x81;	 // hexidecimal representation of black rooks in starting position
	blackQueens = 0x8;	 // hexidecimal representation of black queens in starting position
	blackKing = 0x10;	 // hexidecimal representation of black king in starting position

	bitboards[0][0] = whitePawns;
	bitboards[0][1] = whiteKnights;
	bitboards[0][2] = whiteBishops;
	bitboards[0][3] = whiteRooks;
	bitboards[0][4] = whiteQueens;
	bitboards[0][5] = whiteKing;

	bitboards[1][0] = blackPawns;
	bitboards[1][1] = blackKnights;
	bitboards[1][2] = blackBishops;
	bitboards[1][3] = blackRooks;
	bitboards[1][4] = blackQueens;
	bitboards[1][5] = blackKing;
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

void Bitboard::setBit(Color color, PieceType pieceType, Position position)
{
	getBitboard(color, pieceType) |= 1ULL << getSquareNumber(position);
}

void Bitboard::clearBit(Color color, PieceType pieceType, Position position)
{
	getBitboard(color, pieceType) &= ~(1ULL << getSquareNumber(position));
}