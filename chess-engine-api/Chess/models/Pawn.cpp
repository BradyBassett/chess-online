#include "Pawn.h"
#include "Square.h"

bool Pawn::canMoveOneSquare(Board &board, Position targetPosition) const
{
	return currentPosition.row == targetPosition.row + singleStepDirection;
}

bool Pawn::canMoveTwoSquares(Board &board, Position targetPosition) const
{
	return currentPosition.row == targetPosition.row + doubleStepDirection;
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
		if (!canMoveOneSquare(board, targetPosition))
		{
			errorMessage = "Invalid move - Pawn can only move one square forward after its first move";
			return false;
		}
	}
	else
	{
		if (!canMoveOneSquare(board, targetPosition) && !canMoveTwoSquares(board, targetPosition))
		{
			errorMessage = "Invalid move - Pawn can only move one or two squares forward on its first move";
			return false;
		}
	}

	return true;
}

Bitboard Pawn::getValidMoves(Board &board) const
{
	Bitboard validMoves = 0x0;

	if (hasMoved)
	{
		Position targetPosition = {currentPosition.row + singleStepDirection, currentPosition.col};
		if (targetPosition.row >= 0 && targetPosition.row < 8 && targetPosition.col >= 0 && targetPosition.col < 8)
		{
			std::string errorMessage;
			if (isValidMove(board, targetPosition, errorMessage))
			{
				validMoves.setBit(targetPosition);
			}
		}
	}
	else
	{
		Position targetPositions[2] = {{currentPosition.row + singleStepDirection, currentPosition.col},
									   {currentPosition.row + doubleStepDirection, currentPosition.col}};
		for (const Position &targetPosition : targetPositions)
		{
			if (targetPosition.row >= 0 && targetPosition.row < 8 && targetPosition.col >= 0 && targetPosition.col < 8)
			{
				std::string errorMessage;
				if (isValidMove(board, targetPosition, errorMessage))
				{
					validMoves.setBit(targetPosition);
				}
			}
		}
	}
}

bool Pawn::canPromote(Position targetPosition) const
{
	return (pieceColor == Color::White && targetPosition.row == 0) || (pieceColor == Color::Black && targetPosition.row == 7);
}