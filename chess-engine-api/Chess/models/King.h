#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : virtual public Piece {
public:
	King(Color pieceColor, Position currentPosition);

	bool isValidMove(Board& board, Position targetPosition, std::string& errorMessage) const;
};

#endif
