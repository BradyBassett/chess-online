#include "King.h"
#include "Rook.h"
#include "Square.h"
#include "../structs/Position.h"

const Position King::moves[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

bool King::getIsValidCastle(Board &board, Position targetPosition, std::string &errorMessage) const
{
	// If king is trying to castle queen side get the rook on the queen side and vice versa
	Side side = targetPosition.col == 2 ? Side::QueenSide : Side::KingSide;
	std::shared_ptr<Rook> rook = board.getRook(pieceColor, side);

	if (hasMoved)
	{
		errorMessage = "Invalid move - King has already moved";
		return false;
	}
	else if (rook->getHasMoved())
	{
		std::string rookSide = side == Side::QueenSide ? "Queenside " : "Kingside ";
		errorMessage = "Invalid move - " + rookSide + "Rook has already moved";
		return false;
	}
	else if (isInCheck)
	{
		errorMessage = "Invalid move - King is in check";
		return false;
	}

	int direction = side == Side::QueenSide ? -1 : 1;
	for (int i = currentPosition.col + direction; i != rook->getCurrentPosition().col; i + direction)
	{
		Square &square = board.getSquare(currentPosition.row, i);
		// If there is a piece between the king and the rook then the king cannot castle
		if (square.getPiece() != nullptr)
		{
			errorMessage = "Invalid move - King cannot castle through other pieces";
			return false;
		} // todo - check if the king passes through check
	}

	return true;
}

King::King(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition)
{
	pieceType = PieceType::King;
}

bool King::isValidMove(Game &game, Position targetPosition, std::string &errorMessage) const
{
	if (!Piece::isValidMove(game, targetPosition, errorMessage))
	{
		return false;
	}

	// If the target position is two squares away from the king then it is a castle
	if ((targetPosition.col == 2 && targetPosition.row == currentPosition.row) ||
		(targetPosition.col == 6 && targetPosition.row == currentPosition.row))
	{
		return getIsValidCastle(game.getBoard(), targetPosition, errorMessage);
		// Otherwise, the king can only move one square in any direction
	}
	else
	{
		for (const Position &move : moves)
		{
			if (targetPosition.row == currentPosition.row + move.row &&
				targetPosition.col == currentPosition.col + move.col)
			{
				return true;
			}
		}

		errorMessage = "Invalid move - King can only move one square in any direction";
		return false;
	}
}

Bitboard King::getValidMoves(Game &game) const
{
	Bitboard validMoves = 0x0;

	for (const Position &move : moves)
	{
		Position targetPosition = {currentPosition.row + move.row, currentPosition.col + move.col};

		if (targetPosition.row >= 0 && targetPosition.row < 8 && targetPosition.col >= 0 && targetPosition.col < 8)
		{
			std::string errorMessage;
			if (isValidMove(game, targetPosition, errorMessage))
			{
				validMoves.setBit(targetPosition);
			}
		}
	}
}

bool King::getIsInCheck() const
{
	return isInCheck;
}

void King::setIsInCheck(bool value)
{
	isInCheck = value;
}
