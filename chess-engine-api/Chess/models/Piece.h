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

	virtual bool isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const;

	virtual Bitboard getValidMoves(Board &board, int (&directions)[4][2]) const;

	bool getHasMoved() const;

	void setHasMoved();

	bool getIsCaptured() const;

	Color getPieceColor() const;

	PieceType getPieceType() const;

	Position getCurrentPosition() const;

	void setCurrentPosition(Position newPosition);

	virtual bool canPromote(Position targetPosition) const;
};

#include "Board.h"

#endif