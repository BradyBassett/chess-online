#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include "../enums/PieceType.h"
#include "../enums/Color.h"

class Bitboard
{
private:
	uint64_t bitboards[2][6]; // [color][pieceType] = [white, black][pawns, knights, bishops, rooks, queens, king]

	uint64_t whitePawns;
	uint64_t whiteKnights;
	uint64_t whiteBishops;
	uint64_t whiteRooks;
	uint64_t whiteQueens;
	uint64_t whiteKing;
	uint64_t whitePieces; // maybe remove this

	uint64_t blackPawns;
	uint64_t blackKnights;
	uint64_t blackBishops;
	uint64_t blackRooks;
	uint64_t blackQueens;
	uint64_t blackKing;
	uint64_t blackPieces; // maybe remove this

	uint64_t allPieces;	   // maybe remove this
	uint64_t emptySquares; // maybe remove this

public:
	Bitboard();

	uint64_t getBitboard(Color color, PieceType pieceType);

	uint64_t getWhitePieces();

	uint64_t getBlackPieces();

	uint64_t getAllPieces();

	void setBit(Color color, PieceType pieceType);

	void clearBit(Color color, PieceType pieceType);
};

#endif