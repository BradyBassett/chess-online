#include "King.h"
#include "Rook.h"
#include "Square.h"
#include "../structs/Position.h"

King::King(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition) {
	pieceType = PieceType::King;
}

bool King::isValidMove(Board& board, Position targetPosition, std::string& errorMessage) const {
	if (!Piece::isValidMove(board, targetPosition, errorMessage)) {
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

	errorMessage = "Invalid move - King can only move one square in any direction";
	return false;
}

bool King::getIsInCheck() const {
	return isInCheck;
}

void King::setIsInCheck(bool value) {
	isInCheck = value;
}

bool King::canCastle(Board& board, Position targetPosition, std::string& errorMessage) const {
	Rook& rook = board.getRook(pieceColor, targetPosition.col == 2 ? Side::QueenSide : Side::KingSide);

	if (hasMoved) {
		errorMessage = "Invalid move - King has already moved";
		return false;
	} else if (rook.getHasMoved()) {
		errorMessage = "Invalid move - Rook has already moved";
		return false;
	} else if (isInCheck) {
		errorMessage = "Invalid move - King is in check";
		return false;
	}

	return true;
}
