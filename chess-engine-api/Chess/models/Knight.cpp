#include "Knight.h"
#include "../structs/Position.h"

Knight::Knight(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition)
{
	pieceType = PieceType::Knight;
}

Bitboard Knight::generateAttacks() const
{
	Bitboard attacks = 0x0;
	const Position moves[8] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

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

Bitboard Knight::getPotentialMoves() const
{
	return generateAttacks();
}