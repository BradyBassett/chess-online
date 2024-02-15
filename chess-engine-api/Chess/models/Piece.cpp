#include <algorithm>
#include <stdexcept>
#include "Piece.h"
#include "Square.h"
#include "Board.h"

Piece::Piece(Color pieceColor, Position currentPosition, PieceType pieceType)
	: pieceColor(pieceColor),
	  currentPosition(currentPosition),
	  pieceType(pieceType)
{
}

Piece::Piece(const Piece &piece) noexcept
	: hasMoved(piece.hasMoved),
	  isCaptured(piece.isCaptured),
	  pieceColor(piece.pieceColor),
	  pieceType(piece.pieceType),
	  currentPosition(piece.currentPosition)
{
}

bool Piece::isValidMove(Board &board, Position targetPosition, std::string &errorMessage) const
{
	// if target square is same as current square return false
	if (targetPosition.row == currentPosition.row && targetPosition.col == currentPosition.col)
	{
		errorMessage = "Invalid move - Piece must move to a different square";
		return false;
	}

	// if target square contains a piece of the same color return false
	Square &targetSquare = board.getSquare(targetPosition.row, targetPosition.col);
	if (targetSquare.getPiece() != nullptr && targetSquare.getPiece()->getPieceColor() == pieceColor)
	{
		errorMessage = "Invalid move - Piece cannot capture a piece of the same color";
		return false;
	}

	return true;
}

Bitboard Piece::getValidMoves(Board &board, int (&directions)[4][2]) const
{
	Bitboard validMoves = 0x0;

	for (const auto &direction : directions)
	{
		for (int x = currentPosition.row + direction[0], y = currentPosition.col + direction[1]; x >= 0 && x < 8 && y >= 0 && y < 8; x += direction[0], y += direction[1])
		{
			Position targetPosition = {x, y};
			std::string errorMessage;
			if (isValidMove(board, targetPosition, errorMessage))
			{
				validMoves.setBit(targetPosition);
			}
			else
			{
				break;
			}
		}
	}

	return validMoves;
}

bool Piece::getHasMoved() const
{
	return hasMoved;
}

void Piece::setHasMoved()
{
	hasMoved = true;
}

bool Piece::getIsCaptured() const
{
	return isCaptured;
}

Color Piece::getPieceColor() const
{
	return pieceColor;
}

PieceType Piece::getPieceType() const
{
	return pieceType;
}

Position Piece::getCurrentPosition() const
{
	return currentPosition;
}

void Piece::setCurrentPosition(Position newPosition)
{
	currentPosition = newPosition;
}

bool Piece::canPromote(Position targetPosition) const
{
	return false;
}