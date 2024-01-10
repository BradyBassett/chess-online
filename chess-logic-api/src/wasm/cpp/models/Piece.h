#ifndef PIECE_H
#define PIECE_H

#include <memory>
#include "Board.h"
#include "Square.h"
#include "PieceType.h"
#include "PieceColor.h"

class Piece {
protected:
	bool hasMoved = false;
	bool isCaptured = false;
	PieceColor color;
	PieceType pieceType;
	Square* currentSquare;

	bool isValidDiagonalMove(Board* board, Square* targetSquare) const;

	bool targetSquareIsDiagonal(Square* targetSquare) const;

	bool isValidStraightMove(Board* board, Square* targetSquare) const;

	bool targetSquareIsStraight(Square* targetSquare) const;

public:
	virtual PieceType getPieceType() const = 0;

	Piece(PieceColor color, Square* currentSquare);

	bool isValidMove(Board* board, Square* targetSquare) const;
};

#endif
