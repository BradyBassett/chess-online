#ifndef QUEEN_H
#define QUEEN_H

#include "DiagonalPiece.h"
#include "OrthagonalPiece.h"

class Queen : virtual public DiagonalPiece, virtual public OrthagonalPiece
{
public:
	Queen(Color pieceColor, Position currentPosition);

	bool isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Board &board) const;

	Bitboard generateAttacks() const;
};

#endif
