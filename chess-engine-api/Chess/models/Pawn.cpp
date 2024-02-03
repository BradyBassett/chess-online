#include "Pawn.h"
#include "Square.h"

bool Pawn::moveOneSquare(Board& board, Position targetPosition) const {
	int moveDirection = pieceColor == Color::White ? 1 : -1;

	return currentPosition.row == targetPosition.row + moveDirection;
}

bool Pawn::moveTwoSquares(Board& board, Position targetPosition) const {
	int moveDirection = pieceColor == Color::White ? 2 : -2;

	return currentPosition.row == targetPosition.row + moveDirection;
}

Pawn::Pawn(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition) {
	pieceType = PieceType::Pawn;
}

bool Pawn::isValidMove(Board& board, Position targetPosition) const {
	if (!Piece::isValidMove(board, targetPosition)) {
		return false;
	}

	if (hasMoved) {
		return moveOneSquare(board, targetPosition);
	}
	else {
		return moveOneSquare(board, targetPosition) || moveTwoSquares(board, targetPosition);
	}
}
