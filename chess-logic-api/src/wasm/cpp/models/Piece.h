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
	PieceColor pieceColor;
	PieceType pieceType;
	Square& currentSquare;

	bool isValidDiagonalMove(Board& board, Square& targetSquare) const;

	bool targetSquareIsDiagonal(Square& targetSquare) const;

	bool isValidStraightMove(Board& board, Square& targetSquare) const;

	bool targetSquareIsStraight(Square& targetSquare) const;

public:
	Piece(PieceColor pieceColor, Square& currentSquare);

	bool isValidMove(Board& board, Square& targetSquare) const;
	
	virtual bool getHasMoved() const = 0;

	virtual bool getIsCaptured() const = 0;

	virtual PieceColor getPieceColor() const = 0;

	virtual PieceType getPieceType() const = 0;
};

#endif
