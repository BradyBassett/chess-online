#include "Pawn.h"
#include "Square.h"

bool Pawn::moveOneSquare(Board &board, Position targetPosition) const
{
	int moveDirection = pieceColor == Color::White ? 1 : -1;

	return currentPosition.row == targetPosition.row + moveDirection;
}

bool Pawn::moveTwoSquares(Board &board, Position targetPosition) const
{
	int moveDirection = pieceColor == Color::White ? 2 : -2;

	return currentPosition.row == targetPosition.row + moveDirection;
}

Pawn::Pawn(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition)
{
	pieceType = PieceType::Pawn;
}

bool Pawn::isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const
{
	if (!Piece::isValidMove(board, targetPosition, errorMessage))
	{
		return false;
	}

	if (hasMoved)
	{
		if (!moveOneSquare(board, targetPosition))
		{
			errorMessage = "Invalid move - Pawn can only move one square forward after its first move";
			return false;
		}
	}
	else
	{
		if (!moveOneSquare(board, targetPosition) && !moveTwoSquares(board, targetPosition))
		{
			errorMessage = "Invalid move - Pawn can only move one or two squares forward on its first move";
			return false;
		}
	}

	return true;
}

bool Pawn::canPromote(Position targetPosition) const
{
	return (pieceColor == Color::White && targetPosition.row == 0) || (pieceColor == Color::Black && targetPosition.row == 7);
}