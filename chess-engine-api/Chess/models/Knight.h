#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : virtual public Piece {
	public:
	Knight(Color pieceColor, Position currentPosition);

	bool isValidMove(Board& board, Position targetPosition, std::string& errorMessage) const;
};

#endif