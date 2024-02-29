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

bool Pawn::isValidMove(Game &game, Position targetPosition, std::string &errorMessage) const
{
	if (!Piece::isValidMove(game, targetPosition, errorMessage))
	{
		return false;
	}

	if (hasMoved)
	{
		if (!canMoveOneSquare(game.getBoard(), targetPosition))
		{
			errorMessage = "Invalid move - Pawn can only move one square forward after its first move";
			return false;
		}
	}
	else
	{
		if (!canMoveOneSquare(game.getBoard(), targetPosition) && !canMoveTwoSquares(game.getBoard(), targetPosition))
		{
			errorMessage = "Invalid move - Pawn can only move one or two squares forward on its first move";
			return false;
		}
	}

	// if there has been at least one move
	if (game.getMoves().size() > 0)
	{
		// if piece is on en passant eligible row
		// if last move was a pawn move of 2 squares that landed next to this pawn
		// then this pawn can capture the other pawn en passant
		int enPassantEligibleRow = pieceColor == Color::White ? 3 : 4;
		Move lastMove = game.getLastMove();

		if (currentPosition.row == enPassantEligibleRow)
		{
			if (!(lastMove.hasFlag(MoveFlag::PawnPush) && (lastMove.to.col == currentPosition.col + 1 || lastMove.to.col == currentPosition.col - 1)))
			{
				errorMessage = "Invalid move - Pawn can only capture en passant if the opponents move was a pawn move of 2 squares that landed next to this pawn";
				return false;
			}
		}
	}

	return true;
}

Bitboard Pawn::getValidMoves(Game &game) const
{
	Bitboard validMoves = 0x0;

	if (hasMoved)
	{
		Position targetPosition = {currentPosition.row + singleStepDirection, currentPosition.col};
		if (targetPosition.row >= 0 && targetPosition.row < 8 && targetPosition.col >= 0 && targetPosition.col < 8)
		{
			std::string errorMessage;
			if (isValidMove(game, targetPosition, errorMessage))
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
				if (isValidMove(game, targetPosition, errorMessage))
				{
					validMoves.setBit(targetPosition);
				}
			}
		}
	}

	return validMoves;
}

bool Pawn::canPromote(Position targetPosition) const
{
	return (pieceColor == Color::White && targetPosition.row == 0) || (pieceColor == Color::Black && targetPosition.row == 7);
}