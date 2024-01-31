#ifndef PIECE_H
#define PIECE_H

#include <memory>
#include "../enums/PieceType.h"
#include "../enums/PieceColor.h"

class Board;
class Square;

class Piece {
protected:
	bool hasMoved = false;
	bool isCaptured = false;
	PieceColor pieceColor;
	PieceType pieceType;
	Square& currentSquare;

public:
	Piece(PieceColor pieceColor, Square& currentSquare);

	virtual bool isValidMove(Board& board, Square& targetSquare) const;

	bool getHasMoved() const;

	bool getIsCaptured() const;

	PieceColor getPieceColor() const;

	PieceType getPieceType() const;

	Square& getCurrentSquare() const;
};

#endif
