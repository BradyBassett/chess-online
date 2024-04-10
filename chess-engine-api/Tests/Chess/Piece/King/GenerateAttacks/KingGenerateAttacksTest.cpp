#include "KingGenerateAttacksTest.hpp"

TEST_F(KingGenerateAttacksTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	King king(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1c141c0000);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(KingGenerateAttacksTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	King king(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x382838000000);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(KingGenerateAttacksTest, generateAttacks_Corner_Black)
{
	Position currentPosition = {0, 0};
	King king(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x302);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(KingGenerateAttacksTest, generateAttacks_Corner_White)
{
	Position currentPosition = {7, 7};
	King king(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x40c0000000000000);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(KingGenerateAttacksTest, generateAttacks_Edge_Black)
{
	Position currentPosition = {0, 3};
	King king(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1c14);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(KingGenerateAttacksTest, generateAttacks_Edge_White)
{
	Position currentPosition = {3, 0};
	King king(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x302030000);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}