#include "Pawn.h"
#include "Square.h"

bool Pawn::moveOneSquare(Board& board, Square& targetSquare) const {
	uint8_t moveDirection = pieceColor == Color::White ? 1 : -1;

	return targetSquare.getRowIndex() == currentSquare->getRowIndex() + moveDirection;
}

bool Pawn::moveTwoSquares(Board& board, Square& targetSquare) const {
	uint8_t moveDirection = pieceColor == Color::White ? 2 : -2;

	return targetSquare.getRowIndex() == currentSquare->getRowIndex() + moveDirection;
}

Pawn::Pawn(Color pieceColor, std::shared_ptr<Square> currentSquare) : Piece(pieceColor, currentSquare) {
	pieceType = PieceType::Pawn;
}

bool Pawn::isValidMove(Board& board, Square& targetSquare) const {
	if (!Piece::isValidMove(board, targetSquare)) {
		return false;
	}

	if (getHasMoved()) {
		return moveOneSquare(board, targetSquare);
	}
	else {
		return moveOneSquare(board, targetSquare) || moveTwoSquares(board, targetSquare);
	}
}
