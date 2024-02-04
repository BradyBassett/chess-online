#include "DiagonalPiece.h"
#include "Square.h"
#include "Board.h"

bool DiagonalPiece::isValidDiagonalMove(Board& board, Position targetPosition) const {
	uint8_t rowStep = (targetPosition.row - currentPosition.row) > 0 ? 1 : -1;
	uint8_t colStep = (targetPosition.col - currentPosition.col) > 0 ? 1 : -1;

	uint8_t i = currentPosition.row + rowStep;
	uint8_t j = currentPosition.col + colStep;

	while ((rowStep > 0 ? i < targetPosition.row : i > targetPosition.row) &&
		   (colStep > 0 ? j < targetPosition.col : j > targetPosition.col)) {
		if (board.getSquare(i, j).getPiece() != nullptr) {
			return false;
		}

		i += rowStep;
		j += colStep;
	}

	return true;
}

bool DiagonalPiece::targetSquareIsDiagonal(Position targetPosition) const {
	return abs(targetPosition.row - currentPosition.row) !=
		   abs(targetPosition.col - currentPosition.col);
}

bool DiagonalPiece::isValidMove(Board& board, Position targetPosition, std::string& errorMessage) const {
	if (!Piece::isValidMove(board, targetPosition, errorMessage)) {
		return false;
	}

	if (!targetSquareIsDiagonal(targetPosition)) {
		errorMessage = "Invalid move - Piece must move diagonally";
		return false;
	}

	if (!isValidDiagonalMove(board, targetPosition)) {
		errorMessage = "Invalid move - Piece cannot jump over other pieces";
		return false;
	}

	return true;
}
