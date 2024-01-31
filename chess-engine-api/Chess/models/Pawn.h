#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : virtual public Piece {
private:
	bool moveOneSquare(Board& board, Square& targetSquare) const;

	bool moveTwoSquares(Board& board, Square& targetSquare) const;

public:
	Pawn(PieceColor pieceColor, Square& currentSquare);

	bool isValidMove(Board& board, Square& targetSquare) const;
};

#endif