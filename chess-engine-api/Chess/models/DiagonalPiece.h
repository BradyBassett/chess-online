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

	bool isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Board &board) const;
};

#endif
