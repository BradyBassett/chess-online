#include "StraightPiece.h"
#include "Square.h"
#include "Board.h"

bool StraightPiece::isValidStraightMove(Board& board, Position targetPosition) const {
	if (targetPosition.row == currentPosition.row) {
		uint8_t rowStart = std::min(targetPosition.col, currentPosition.col);
		uint8_t rowEnd = std::max(targetPosition.col, currentPosition.col);

		for (int i = rowStart + 1; i < rowEnd - 1; i++) {
			if (board.getSquare(currentPosition.row, i).getPiece()) {
				return false;
			}
		}
	}
	else if (targetPosition.col == currentPosition.col) {
		uint8_t colStart = std::min(targetPosition.row, currentPosition.row);
		uint8_t colEnd = std::max(targetPosition.row, currentPosition.row);

		for (int i = colStart + 1; i < colEnd - 1; i++) {
			if (board.getSquare(i, currentPosition.col).getPiece()) {
				return false;
			}
		}
	}
	
	return true;
}

bool StraightPiece::targetSquareIsStraight(Position targetPosition) const {
	return targetPosition.row == currentPosition.row || targetPosition.col == currentPosition.col;
}

bool StraightPiece::isValidMove(Board& board, Position targetPosition) const {
	if (!Piece::isValidMove(board, targetPosition)) {
		return false;
	}

	if (!targetSquareIsStraight(targetPosition)) {
		return false;
	}

	return isValidStraightMove(board, targetPosition);
}
