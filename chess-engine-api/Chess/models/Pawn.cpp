#include "Pawn.h"
#include "Square.h"

bool Pawn::canMoveOneSquare(Position targetPosition) const
{
	return currentPosition.row == targetPosition.row + singleStepDirection && currentPosition.col == targetPosition.col;
}

bool Pawn::canMoveTwoSquares(Position targetPosition) const
{
	return currentPosition.row == targetPosition.row + doubleStepDirection && currentPosition.col == targetPosition.col;
}

Pawn::Pawn(Color pieceColor, Position currentPosition) : Piece(pieceColor, currentPosition)
{
	pieceType = PieceType::Pawn;
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