#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include "../enums/PieceType.h"
#include "../enums/Color.h"
#include "../structs/Position.h"

class Bitboard
{
private:
	uint64_t bitboards[2][6]; // [color][pieceType] = [white, black][pawns, knights, bishops, rooks, queens, king]

	int getSquareNumber(Position position);

public:
	Bitboard();

	uint64_t &getBitboard(Color color, PieceType pieceType);

	uint64_t getWhitePieces();

	uint64_t getBlackPieces();

	uint64_t getAllPieces();

	void setBit(uint64_t &bitboard, Position position);

	void clearBit(uint64_t &bitboard, Position position);
};

#endif