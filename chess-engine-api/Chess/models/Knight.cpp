#include "Knight.h"
#include "Square.h"
#include "../structs/Position.h"

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

	Position moves[] = {
		{2, 1},	  // up 2 right 1
		{2, -1},  // up 2 left 1
		{-2, 1},  // down 2 right 1
		{-2, -1}, // down 2 left 1
		{1, 2},	  // up 1 right 2
		{1, -2},  // up 1 left 2
		{-1, 2},  // down 1 right 2
		{-1, -2}, // down 1 left 2
	};

	for (const auto &move : moves)
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
