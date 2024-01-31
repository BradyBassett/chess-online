#include "StraightPiece.h"
#include "Square.h"
#include "Board.h"

bool StraightPiece::isValidStraightMove(Board& board, Square& targetSquare) const {
	if (targetSquare.getRowIndex() == currentSquare.getRowIndex()) {
		uint8_t rowStart = std::min(targetSquare.getColIndex(), currentSquare.getColIndex());
		uint8_t rowEnd = std::max(targetSquare.getColIndex(), currentSquare.getColIndex());

		for (uint8_t i = rowStart + 1; i < rowEnd - 1; i++) {
			if (board.getSquare(currentSquare.getRowIndex(), i).getPiece()) {
				return false;
			}
		}
	}
	else if (targetSquare.getColIndex() == currentSquare.getColIndex()) {
		uint8_t colStart = std::min(targetSquare.getRowIndex(), currentSquare.getRowIndex());
		uint8_t colEnd = std::max(targetSquare.getRowIndex(), currentSquare.getRowIndex());

		for (uint8_t i = colStart + 1; i < colEnd - 1; i++) {
			if (board.getSquare(i, currentSquare.getColIndex()).getPiece()) {
				return false;
			}
		}
	}
	
	return true;
}

bool StraightPiece::targetSquareIsStraight(Square& targetSquare) const {
	return targetSquare.getRowIndex() == currentSquare.getRowIndex() || targetSquare.getColIndex() == currentSquare.getColIndex();
}

bool StraightPiece::isValidMove(Board& board, Square& targetSquare) const {
	if (!Piece::isValidMove(board, targetSquare)) {
		return false;
	}

	if (!targetSquareIsStraight(targetSquare)) {
		return false;
	}

	return isValidStraightMove(board, targetSquare);
}
