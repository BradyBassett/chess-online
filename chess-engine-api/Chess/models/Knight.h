#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "Game.h"

class Knight : virtual public Piece
{
private:
	static const Position moves[8];

public:
	Knight(Color pieceColor, Position currentPosition);

	bool isValidMove(Game &game, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Game &game) const;
};

#endif