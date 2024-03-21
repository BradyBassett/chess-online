#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : virtual public Piece
{
private:
	bool isInCheck = false;
	bool canCastleKingside = true;
	bool canCastleQueenside = true;

public:
	King(Color pieceColor, Position currentPosition);

	bool getIsInCheck() const;

	void setIsInCheck(bool value);

	bool getCanCastleKingside() const;

	void setCanCastleKingside(bool value);

	bool getCanCastleQueenside() const;

	void setCanCastleQueenside(bool value);

	Bitboard generateAttacks() const;

	Bitboard getPotentialMoves() const;
};

#endif
