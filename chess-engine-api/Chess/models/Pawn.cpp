#include "Pawn.h"
#include "Square.h"

bool Pawn::canMoveOneSquare(Board &board, Position targetPosition) const
{
	return currentPosition.row == targetPosition.row + singleStepDirection;
}

bool Pawn::canMoveTwoSquares(Board &board, Position targetPosition) const
{
	int stepDirection = pieceColor == Color::White ? 1 : -1;
	std::shared_ptr<Piece> piece = board.getSquare(targetPosition.row + stepDirection, targetPosition.col).getPiece();

	if (piece != nullptr)
	{
		return false;
	}

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

	// Diagonal move
	if (abs(targetPosition.col - currentPosition.col) == 1 && abs(targetPosition.row - currentPosition.row) == 1)
	{
		std::shared_ptr<Piece> targetPiece = board.getSquare(targetPosition).getPiece();
		if (targetPiece == nullptr)
		{
			int enPassantEligibleRow = pieceColor == Color::White ? 3 : 4;
			if (currentPosition.row == enPassantEligibleRow)
			{
				Square *enPassantTargetSquare = board.getEnPassantTargetSquare();
				if (enPassantTargetSquare == nullptr || targetPosition != board.getEnPassantTargetSquare()->getPosition())
				{
					errorMessage = "Invalid move - Pawn can only capture en passant if the opponents move was a pawn move of 2 squares that landed next to this pawn";
					return false;
				}
			}
			else
			{
				errorMessage = "Invalid move - Pawn cannot move diagonally unless it is capturing an opponent's piece";
				return false;
			}
		}
		else
		{
			if (targetPiece->getPieceColor() == pieceColor)
			{
				errorMessage = "Invalid move - Pawn can only capture pieces of the opposite color";
				return false;
			}
		}
	}
	// Orthagonal move
	else
	{
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
				errorMessage = "Invalid move - Pawn can only move two squares forward if the square in front of it is empty and it is its first move";
				return false;
			}
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

	return validMoves;
}

bool Pawn::canPromote(Position targetPosition) const
{
	return (pieceColor == Color::White && targetPosition.row == 0) || (pieceColor == Color::Black && targetPosition.row == 7);
}

Bitboard Pawn::generateAttacks() const
{
	Bitboard attacks = 0x0;

	int direction = pieceColor == Color::White ? -1 : 1;

	Position targetPositions[2] = {{currentPosition.row + direction, currentPosition.col - 1},
								   {currentPosition.row + direction, currentPosition.col + 1}};

	for (const Position &targetPosition : targetPositions)
	{
		if (targetPosition.row >= 0 && targetPosition.row < 8 && targetPosition.col >= 0 && targetPosition.col < 8)
		{
			attacks.setBit(targetPosition);
		}
	}

	return attacks;
}