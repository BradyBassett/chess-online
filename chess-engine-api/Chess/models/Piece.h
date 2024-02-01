#ifndef PIECE_H
#define PIECE_H

#include <memory>
#include "../enums/PieceType.h"
#include "../enums/Color.h"
#include "Board.h"

class Square;

class Piece {
protected:
	bool hasMoved = false;
	bool isCaptured = false;
	Color pieceColor;
	PieceType pieceType;
	std::shared_ptr<Square> currentSquare;

public:
	Piece(Color pieceColor, std::shared_ptr<Square> currentSquare);

	Piece(const Piece& piece) noexcept;

	virtual bool isValidMove(Board& board, Square& targetSquare) const;

	bool getHasMoved() const;

	bool getIsCaptured() const;

	Color getPieceColor() const;

	PieceType getPieceType() const;

	std::shared_ptr<Square> getCurrentSquare() const;
};

#endif
