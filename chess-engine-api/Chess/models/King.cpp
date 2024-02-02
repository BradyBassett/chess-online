#include "King.h"
#include "Square.h"
#include "../structs/Position.h"

King::King(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition) {
	pieceType = PieceType::King;
}

bool King::isValidMove(Board& board, Position targetPosition) const {
	if (!Piece::isValidMove(board, targetPosition)) {
		return false;
	}

	Position moves[] = {
		{1, 0},		// Up
		{1, 1},		// Up-Right
		{0, 1},		// Right
		{-1, 1},	// Down-Right
		{-1, 0},	// Down
		{-1, -1},	// Down-Left
		{0, -1},	// Left
		{1, -1}		// Up-Left
	};

	for (const auto& move : moves) {
		if (targetPosition.row == currentPosition.row + move.row &&
				targetPosition.col == currentPosition.col + move.col) {
			return true;
		}
	}

	return false;
}
