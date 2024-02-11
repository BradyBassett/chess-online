#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : virtual public Piece
{
private:
	bool isInCheck = false;

	bool getIsValidCastle(Board &board, Position targetPosition, std::string &errorMessage) const;

public:
	King(Color pieceColor, Position currentPosition);

	bool isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const;

	bool getIsInCheck() const;

	void setIsInCheck(bool value);
};

#endif
