#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "Game.h"

class King : virtual public Piece
{
private:
	bool isInCheck = false;

	bool getIsValidCastle(Board &board, Position targetPosition, std::string &errorMessage) const;

	static const Position moves[8];

public:
	King(Color pieceColor, Position currentPosition);

	bool isValidMove(Game &game, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Game &game) const;

	bool getIsInCheck() const;

	void setIsInCheck(bool value);
};

#endif
