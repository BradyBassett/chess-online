#include "King.h"
#include "Rook.h"
#include "../structs/Position.h"

King::King(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition)
{
	pieceType = PieceType::King;
}

bool King::getIsInCheck() const
{
	return isInCheck;
}

void King::setIsInCheck(bool value)
{
	isInCheck = value;
}

Bitboard King::generateAttacks() const
{
	const Position moves[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
	Bitboard attacks = 0x0;

	for (const Position &move : moves)
	{
		Position targetPosition = {currentPosition.row + move.row, currentPosition.col + move.col};

		if (targetPosition.row >= 0 && targetPosition.row < 8 && targetPosition.col >= 0 && targetPosition.col < 8)
		{
			attacks.setBit(targetPosition);
		}
	}

	return attacks;
}