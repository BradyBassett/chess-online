#include "StraightPiece.h"
#include "Square.h"

bool StraightPiece::isValidStraightMove(Board &board, Position targetPosition) const
{
	if (targetPosition.row == currentPosition.row)
	{
		uint8_t rowStart = std::min(targetPosition.col, currentPosition.col);
		uint8_t rowEnd = std::max(targetPosition.col, currentPosition.col);

		for (int i = rowStart + 1; i < rowEnd - 1; i++)
		{
			if (board.getSquare(currentPosition.row, i).getPiece())
			{
				return false;
			}
		}
	}
	else if (targetPosition.col == currentPosition.col)
	{
		uint8_t colStart = std::min(targetPosition.row, currentPosition.row);
		uint8_t colEnd = std::max(targetPosition.row, currentPosition.row);

		for (int i = colStart + 1; i < colEnd - 1; i++)
		{
			if (board.getSquare(i, currentPosition.col).getPiece())
			{
				return false;
			}
		}
	}

	return true;
}

bool StraightPiece::targetSquareIsStraight(Position targetPosition) const
{
	return targetPosition.row == currentPosition.row || targetPosition.col == currentPosition.col;
}

bool StraightPiece::isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const
{
	if (!Piece::isValidMove(board, targetPosition, errorMessage))
	{
		return false;
	}

	if (!targetSquareIsStraight(targetPosition))
	{
		errorMessage = "Invalid move - Piece must move straight";
		return false;
	}

	if (!isValidStraightMove(board, targetPosition))
	{
		errorMessage = "Invalid move - Piece cannot jump over other pieces";
		return false;
	}

	return true;
}

Bitboard StraightPiece::getValidMoves(Board &board) const
{
	int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	return Piece::getValidMoves(board, directions);
}
