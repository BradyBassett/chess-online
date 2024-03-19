#ifndef PIECE_H
#define PIECE_H

#include <memory>
#include "../enums/PieceType.h"
#include "../enums/Color.h"
#include "../structs/Position.h"
#include "Bitboard.h"

class Board;

class Piece
{
protected:
	bool hasMoved = false;
	bool isCaptured = false;
	Color pieceColor;
	PieceType pieceType;
	Position currentPosition;

public:
	Piece(Color pieceColor, Position currentPosition, PieceType pieceType = PieceType::Unknown);

	Piece(const Piece &piece) noexcept;

	bool getHasMoved() const;

	void setHasMoved();

	bool getIsCaptured() const;

	Color getPieceColor() const;

	PieceType getPieceType() const;

	Position getCurrentPosition() const;

	void setCurrentPosition(Position newPosition);

	virtual bool canPromote(Position targetPosition) const;

	Bitboard generateAttacks(const Position (&directions)[4]) const;
};

#include "Board.h"

#endif