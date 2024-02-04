#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : virtual public Piece {
private:
	bool moveOneSquare(Board& board, Position targetPosition) const;

	bool moveTwoSquares(Board& board, Position targetPosition) const;

public:
	Pawn(Color pieceColor, Position currentPosition);

	bool isValidMove(Board& board, Position targetPosition, std::string& errorMessage) const;

	bool canPromote(Position targetPosition) const override;
};

#endif