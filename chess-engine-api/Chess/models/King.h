#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : virtual public Piece {
public:
	King(PieceColor pieceColor, Square& currentSquare);

	bool isValidMove(Board& board, Square& targetSquare) const;
};

#endif
