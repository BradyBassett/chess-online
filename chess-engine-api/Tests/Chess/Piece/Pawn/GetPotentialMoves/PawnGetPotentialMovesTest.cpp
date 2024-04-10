#include "PawnGetPotentialMovesTest.h"

TEST_F(PawnGetPotentialMovesTest, GetPotentialMoves_WhitePawnHasNotMoved)
{
	Position currentPosition = {6, 4};
	Pawn pawn(Color::White, currentPosition);

	pawn.setHasMoved(false);

	Bitboard expectedMoves = Bitboard(0x381000000000);
	Bitboard actualMoves = pawn.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST_F(PawnGetPotentialMovesTest, GetPotentialMoves_BlackPawnHasNotMoved)
{
	Position currentPosition = {1, 3};
	Pawn pawn(Color::Black, currentPosition);

	pawn.setHasMoved(false);

	Bitboard expectedMoves = Bitboard(0x81c0000);
	Bitboard actualMoves = pawn.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST_F(PawnGetPotentialMovesTest, GetPotentialMoves_WhitePawnMoved)
{
	Position currentPosition = {4, 4};
	Pawn pawn(Color::White, currentPosition);

	pawn.setHasMoved(true);

	Bitboard expectedMoves = Bitboard(0x38000000);
	Bitboard actualMoves = pawn.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST_F(PawnGetPotentialMovesTest, GetPotentialMoves_BlackPawnMoved)
{
	Position currentPosition = {4, 4};
	Pawn pawn(Color::Black, currentPosition);

	pawn.setHasMoved(true);

	Bitboard expectedMoves = Bitboard(0x380000000000);
	Bitboard actualMoves = pawn.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}