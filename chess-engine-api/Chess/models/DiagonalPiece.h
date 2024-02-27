#ifndef DIAGONALPIECE_H
#define DIAGONALPIECE_H

#include "Piece.h"

class DiagonalPiece : virtual public Piece
{
private:
	bool isValidDiagonalMove(Board &board, Position targetPosition) const;

	bool targetSquareIsDiagonal(Position targetPosition) const;

public:
	using Piece::Piece;

	bool isValidMove(Game &game, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Game &game) const;
};

#endif
