#include "KnightGenerateAttacksTest.h"

TEST_F(KnightGenerateAttacksTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	Knight knight(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x142200221400);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(KnightGenerateAttacksTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	Knight knight(Color::White, currentPosition);
	Bitboard expectedAttacks = Bitboard(0x28440044280000);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(KnightGenerateAttacksTest, generateAttacks_Corner_Black)
{
	Position currentPosition = {0, 0};
	Knight knight(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x20400);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(KnightGenerateAttacksTest, generateAttacks_Corner_White)
{
	Position currentPosition = {7, 7};
	Knight knight(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x20400000000000);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(KnightGenerateAttacksTest, generateAttacks_Edge_Black)
{
	Position currentPosition = {0, 3};
	Knight knight(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x142200);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(KnightGenerateAttacksTest, generateAttacks_Edge_White)
{
	Position currentPosition = {3, 0};
	Knight knight(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x20400040200);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}