#ifndef QUEEN_H
#define QUEEN_H

#include "DiagonalPiece.h"
#include "StraightPiece.h"

class Queen : virtual public DiagonalPiece, virtual public StraightPiece {
public:
	Queen(PieceColor pieceColor, Square& currentSquare);

	bool isValidMove(Board& board, Square& targetSquare) const;
};

#endif
