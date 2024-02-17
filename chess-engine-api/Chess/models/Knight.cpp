#include "Knight.h"
#include "Square.h"
#include "../structs/Position.h"

static const Position moves[8] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

Knight::Knight(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition)
{
	pieceType = PieceType::Knight;
}

bool Knight::isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const
{
	if (!Piece::isValidMove(board, targetPosition, errorMessage))
	{
		return false;
	}

	for (const Position &move : moves)
	{
		if (targetPosition.row == currentPosition.row + move.row &&
			targetPosition.col == currentPosition.col + move.col)
		{
			return true;
		}
	}

	errorMessage = "Invalid move - Knight can only move in an L shape";
	return false;
}

Bitboard Knight::getValidMoves(Board &board) const
{
	Bitboard validMoves = 0x0;

	for (const Position &move : moves)
	{
		Position targetPosition = {currentPosition.row + move.row, currentPosition.col + move.col};

		if (targetPosition.row >= 0 && targetPosition.row < 8 && targetPosition.col >= 0 && targetPosition.col < 8)
		{
			std::string errorMessage;
			if (isValidMove(board, targetPosition, errorMessage))
			{
				validMoves.setBit(targetPosition);
			}
		}
	}

	return validMoves;
}