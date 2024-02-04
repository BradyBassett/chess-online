#include <algorithm>
#include <stdexcept>
#include "Piece.h"
#include "Square.h"

Piece::Piece(Color pieceColor, Position currentPosition)
	: pieceColor(pieceColor),
		currentPosition(currentPosition) {
}

Piece::Piece(const Piece& piece) noexcept
	: hasMoved(piece.hasMoved),
		isCaptured(piece.isCaptured),
		pieceColor(piece.pieceColor),
		pieceType(piece.pieceType),
		currentPosition(piece.currentPosition) {
}

bool Piece::isValidMove(Board& board, Position targetPosition) const {
	// if target square is same as current square return false
	if (targetPosition.row == currentPosition.row && targetPosition.col == currentPosition.col) {
		return false;
	}

	// if target square contains a piece of the same color return false
	Square& targetSquare = board.getSquare(targetPosition.row, targetPosition.col);
	if (targetSquare.getPiece() != nullptr && targetSquare.getPiece()->getPieceColor() == pieceColor) {
		return false;
	}

	return true;
}

bool Piece::getHasMoved() const {
	return hasMoved;
}

void Piece::setHasMoved() {
	hasMoved = true;
}

bool Piece::getIsCaptured() const {
	return isCaptured;
}

Color Piece::getPieceColor() const {
	return pieceColor;
}

PieceType Piece::getPieceType() const {
	return pieceType;
}

Position Piece::getCurrentPosition() const {
	return currentPosition;
}

bool Piece::canPromote(Position targetPosition) const {
	return false;
}