#ifndef PIECE_H
#define PIECE_H

#include <memory>
#include "../enums/PieceType.h"
#include "../enums/Color.h"
#include "Square.h"
#include "Board.h"

class Piece {
protected:
	bool hasMoved = false;
	bool isCaptured = false;
	Color pieceColor;
	PieceType pieceType;
	Square& currentSquare;

public:
	Piece(Color pieceColor, Square& currentSquare);

	virtual bool isValidMove(Board& board, Square& targetSquare) const;

	bool getHasMoved() const;

	bool getIsCaptured() const;

	Color getPieceColor() const;

	PieceType getPieceType() const;

	Square& getCurrentSquare() const;
};

#endif
