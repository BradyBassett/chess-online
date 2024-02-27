#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : virtual public Piece
{
private:
	const int singleStepDirection = pieceColor == Color::White ? 1 : -1;
	const int doubleStepDirection = pieceColor == Color::White ? 2 : -2;

	bool canMoveOneSquare(Board &board, Position targetPosition) const;

	bool canMoveTwoSquares(Board &board, Position targetPosition) const;

public:
	Pawn(Color pieceColor, Position currentPosition);

	bool isValidMove(Game &game, Position targetPosition, std::string &errorMessage) const;

	Bitboard getValidMoves(Game &game) const;

	bool canPromote(Position targetPosition) const override;
};

#endif