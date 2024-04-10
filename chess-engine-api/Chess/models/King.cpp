#include "King.hpp"
#include "Rook.hpp"
#include "../structs/Position.hpp"

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

bool King::getCanCastleKingside() const
{
	return canCastleKingside;
}

void King::setCanCastleKingside(bool value)
{
	canCastleKingside = value;
}

bool King::getCanCastleQueenside() const
{
	return canCastleQueenside;
}

void King::setCanCastleQueenside(bool value)
{
	canCastleQueenside = value;
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

Bitboard King::getPotentialMoves() const
{
	Bitboard moves = generateAttacks();

	if (canCastleKingside)
	{
		moves.setBit({currentPosition.row, currentPosition.col + 2});
	}
	if (canCastleQueenside)
	{
		moves.setBit({currentPosition.row, currentPosition.col - 2});
	}

	return moves;
}