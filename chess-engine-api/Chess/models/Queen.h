#ifndef QUEEN_H
#define QUEEN_H

#include "DiagonalPiece.h"
#include "StraightPiece.h"

class Queen : virtual public DiagonalPiece, virtual public StraightPiece {
public:
	Queen(Color pieceColor, Position currentPosition);

	bool isValidMove(Board& board, Position targetPosition) const;
};

#endif
