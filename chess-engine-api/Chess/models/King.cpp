#include "King.h"
#include "Rook.h"
#include "Square.h"
#include "../structs/Position.h"

bool King::getIsValidCastle(Board& board, Position targetPosition, std::string& errorMessage) const {
	// If king is trying to castle queen side get the rook on the queen side and vice versa
	Side side = targetPosition.col == 2 ? Side::QueenSide : Side::KingSide;
	std::shared_ptr<Rook> rook = board.getRook(pieceColor, side);

	if (hasMoved) {
		errorMessage = "Invalid move - King has already moved";
		return false;
	} else if (rook->getHasMoved()) {
		std::string rookSide = side == Side::QueenSide ? "Queenside " : "Kingside ";
		errorMessage = "Invalid move - " + rookSide + "Rook has already moved";
		return false;
	} else if (isInCheck) {
		errorMessage = "Invalid move - King is in check";
		return false;
	}

	return true;
}

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

	// If the target position is two squares away from the king then it is a castle
	if ((targetPosition.col == 2 && targetPosition.row == currentPosition.row) ||
			(targetPosition.col == 6 && targetPosition.row == currentPosition.row)) {
		return getIsValidCastle(board, targetPosition, errorMessage);
	// Otherwise, the king can only move one square in any direction
	} else {
		for (const auto& move : moves) {
			if (targetPosition.row == currentPosition.row + move.row &&
					targetPosition.col == currentPosition.col + move.col) {
				return true;
			}
		}

		errorMessage = "Invalid move - King can only move one square in any direction";
		return false;
	}
}

bool King::getIsInCheck() const {
	return isInCheck;
}

void King::setIsInCheck(bool value) {
	isInCheck = value;
}
