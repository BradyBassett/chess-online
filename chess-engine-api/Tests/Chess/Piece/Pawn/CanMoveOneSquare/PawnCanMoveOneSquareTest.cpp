#include "PawnCanMoveOneSquareTest.hpp"

TEST_F(PawnCanMoveOneSquareTest, CanMoveOneSquare_ValidMove_White)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {1, 3};
	Pawn pawn(Color::White, currentPosition);

	bool result = pawn.canMoveOneSquare(targetPosition);

	ASSERT_TRUE(result);
}

TEST_F(PawnCanMoveOneSquareTest, CanMoveOneSquare_ValidMove_Black)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {3, 3};
	Pawn pawn(Color::Black, currentPosition);

	bool result = pawn.canMoveOneSquare(targetPosition);

	ASSERT_TRUE(result);
}

TEST_F(PawnCanMoveOneSquareTest, CanMoveOneSquare_InvalidMove_White)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {0, 3};
	Pawn pawn(Color::White, currentPosition);

	bool result = pawn.canMoveOneSquare(targetPosition);

	ASSERT_FALSE(result);
}

TEST_F(PawnCanMoveOneSquareTest, CanMoveOneSquare_InvalidMove_Black)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {4, 3};
	Pawn pawn(Color::Black, currentPosition);

	bool result = pawn.canMoveOneSquare(targetPosition);

	ASSERT_FALSE(result);
}