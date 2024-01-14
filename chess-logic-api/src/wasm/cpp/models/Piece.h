#ifndef PIECE_H
#define PIECE_H

#include <memory>
#include "../utils/enums/PieceType.h"
#include "../utils/enums/PieceColor.h"

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

	bool isValidMove(Board& board, Square& targetSquare) const;
	
	virtual bool getHasMoved() const;

	virtual bool getIsCaptured() const;

	virtual PieceColor getPieceColor() const;

	virtual PieceType getPieceType() const;
};

#endif
