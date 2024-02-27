#ifndef QUEEN_H
#define QUEEN_H

#include "DiagonalPiece.h"
#include "StraightPiece.h"

class Queen : virtual public DiagonalPiece, virtual public StraightPiece
{
public:
	Queen(Color pieceColor, Position currentPosition);

	bool isValidMove(Game &game, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Game &game) const;
};

#endif
