#ifndef STRAIGHTPIECE_H
#define STRAIGHTPIECE_H

#include "Piece.h"
#include "Board.h"

class OrthagonalPiece : virtual public Piece
{
private:
	bool isValidOrthagonalMove(Board &board, Position targetPosition) const;

	bool targetSquareIsOrthagonal(Position targetPosition) const;

public:
	using Piece::Piece;

	bool isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Board &board) const;

	Bitboard generateAttacks() const;
};

#endif
