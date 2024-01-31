#include "Knight.h"
#include "Square.h"
#include "../structs/TargetPos.h"

Knight::Knight(PieceColor pieceColor, Square& currentSquare) : Piece(pieceColor, currentSquare) {
	pieceType = PieceType::Knight;
}

bool Knight::isValidMove(Board& board, Square& targetSquare) const {
	if (!Piece::isValidMove(board, targetSquare)) {
		return false;
	}

	TargetPos moves[] = {
		{2, 1}, // up 2 right 1
		{2, -1}, // up 2 left 1
		{-2, 1}, // down 2 right 1
		{-2, -1}, // down 2 left 1
		{1, 2}, // up 1 right 2
		{1, -2}, // up 1 left 2
		{-1, 2}, // down 1 right 2
		{-1, -2}, // down 1 left 2
	};

	for (const auto& move : moves) {
		if (targetSquare.getRowIndex() == currentSquare.getRowIndex() + move.row &&
				targetSquare.getColIndex() == currentSquare.getColIndex() + move.col) {
			return true;
		}
	}

	return false;
}
