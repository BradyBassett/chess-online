#include "PawnGenerateAttacksTest.h"

TEST_F(PawnGenerateAttacksTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	Pawn pawn(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1400000000);
	Bitboard actualAttacks = pawn.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(PawnGenerateAttacksTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	Pawn pawn(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x28000000);
	Bitboard actualAttacks = pawn.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(PawnGenerateAttacksTest, GenerateAttacks_Edge_Black)
{
	Position currentPosition = {3, 0};
	Pawn pawn(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x200000000);
	Bitboard actualAttacks = pawn.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(PawnGenerateAttacksTest, GenerateAttacks_Edge_White)
{
	Position currentPosition = {5, 7};
	Pawn pawn(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x4000000000);
	Bitboard actualAttacks = pawn.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}