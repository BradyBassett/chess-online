#include "PawnCanPromoteTest.hpp"

TEST_F(PawnCanPromoteTest, CanPromote_WhitePawnOnLastRow)
{
	Position targetPosition = {0, 7};
	Pawn pawn(Color::White, targetPosition);

	ASSERT_TRUE(pawn.canPromote(targetPosition));
}

TEST_F(PawnCanPromoteTest, CanPromote_WhitePawnNotOnLastRow)
{
	Position targetPosition = {3, 4};
	Pawn pawn(Color::White, targetPosition);

	ASSERT_FALSE(pawn.canPromote(targetPosition));
}

TEST_F(PawnCanPromoteTest, CanPromote_BlackPawnOnLastRow)
{
	Position targetPosition = {7, 0};
	Pawn pawn(Color::Black, targetPosition);

	ASSERT_TRUE(pawn.canPromote(targetPosition));
}

TEST_F(PawnCanPromoteTest, CanPromote_BlackPawnNotOnLastRow)
{
	Position targetPosition = {2, 5};
	Pawn pawn(Color::Black, targetPosition);

	ASSERT_FALSE(pawn.canPromote(targetPosition));
}
