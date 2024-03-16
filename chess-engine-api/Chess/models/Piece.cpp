#include <algorithm>
#include <stdexcept>
#include "Piece.h"

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

Bitboard Piece::generateAttacks(const Position (&directions)[4]) const
{
	Bitboard attacks = 0x0;

	for (const Position &direction : directions)
	{
		for (int i = currentPosition.row + direction.row, j = currentPosition.col + direction.col; i >= 0 && i < 8 && j >= 0 && j < 8; i += direction.row, j += direction.col)
		{
			attacks.setBit({i, j});
		}
	}

	return attacks;
}

// The attack table parameter is going to be the bitboard at the pieces current position, determined by the piece's type and color when the function is called
bool Piece::canMoveTo(const Position &targetPosition, Bitboard attackTable) const
{
	Bitboard target = Bitboard(targetPosition);

	return (attackTable & target) != 0;
}