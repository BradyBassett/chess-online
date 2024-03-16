#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : virtual public Piece
{
private:
	bool isInCheck = false;

public:
	King(Color pieceColor, Position currentPosition);

	bool getIsInCheck() const;

	void setIsInCheck(bool value);

	Bitboard generateAttacks() const;
};

#endif
