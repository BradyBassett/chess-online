#include "Pawn.h"
#include "Square.h"

bool Pawn::moveOneSquare(Board& board, Position targetPosition) const {
	uint8_t moveDirection = pieceColor == Color::White ? 1 : -1;

	return targetPosition.row == currentPosition.row + moveDirection;
}

bool Pawn::moveTwoSquares(Board& board, Position targetPosition) const {
	uint8_t moveDirection = pieceColor == Color::White ? 2 : -2;

	return targetPosition.row == currentPosition.row + moveDirection;
}

Pawn::Pawn(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition) {
	pieceType = PieceType::Pawn;
}

bool Pawn::isValidMove(Board& board, Position targetPosition) const {
	if (!Piece::isValidMove(board, targetPosition)) {
		return false;
	}

	if (getHasMoved()) {
		return moveOneSquare(board, targetPosition);
	}
	else {
		return moveOneSquare(board, targetPosition) || moveTwoSquares(board, targetPosition);
	}
}
