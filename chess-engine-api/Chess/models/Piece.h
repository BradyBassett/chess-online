#ifndef PIECE_H
#define PIECE_H

#include <memory>
#include "../enums/PieceType.h"
#include "../enums/Color.h"
#include "../structs/Position.h"

class Board;

class Piece {
protected:
	bool hasMoved = false;
	bool isCaptured = false;
	Color pieceColor;
	PieceType pieceType;
	Position currentPosition;

public:
	Piece(Color pieceColor, Position currentPosition);

	Piece(const Piece& piece) noexcept;

	virtual bool isValidMove(Board& board, Position targetPosition) const;

	bool getHasMoved() const;

	bool getIsCaptured() const;

	Color getPieceColor() const;

	PieceType getPieceType() const;

	Position getCurrentPosition() const;
};

#include "Board.h"

#endif
