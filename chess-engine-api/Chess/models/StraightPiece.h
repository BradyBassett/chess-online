#ifndef STRAIGHTPIECE_H
#define STRAIGHTPIECE_H

#include "Piece.h"
#include "Game.h"

class StraightPiece : virtual public Piece
{
private:
	bool isValidStraightMove(Board &board, Position targetPosition) const;

	bool targetSquareIsStraight(Position targetPosition) const;

public:
	using Piece::Piece;

	bool isValidMove(Game &game, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Game &game) const;
};

#endif
