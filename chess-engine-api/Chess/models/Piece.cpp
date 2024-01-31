#include <algorithm>
#include "Piece.h"
#include "Square.h"

Piece::Piece(PieceColor pieceColor, Square& currentSquare)
	: pieceColor(pieceColor),
		currentSquare(currentSquare) {
}

bool Piece::isValidMove(Board& board, Square& targetSquare) const {
	if (&targetSquare == &currentSquare) {
		return false;
	}

	if (targetSquare.getPiece() && targetSquare.getPiece()->getPieceColor() == pieceColor) {
		return false;
	}

	return true;
}

bool Piece::getHasMoved() const {
	return hasMoved;
}

bool Piece::getIsCaptured() const {
	return isCaptured;
}

PieceColor Piece::getPieceColor() const {
	return pieceColor;
}

PieceType Piece::getPieceType() const {
	return pieceType;
}

Square& Piece::getCurrentSquare() const {
	return currentSquare;
}
