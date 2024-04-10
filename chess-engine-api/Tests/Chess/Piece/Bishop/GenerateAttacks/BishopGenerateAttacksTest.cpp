#include "BishopGenerateAttacksTest.hpp"

TEST_F(BishopGenerateAttacksTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	Bishop bishop(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8041221400142241);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(BishopGenerateAttacksTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	Bishop bishop(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8244280028448201);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(BishopGenerateAttacksTest, generateAttacks_Corner_Black)
{
	Position currentPosition = {0, 0};
	Bishop bishop(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8040201008040200);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(BishopGenerateAttacksTest, generateAttacks_Corner_White)
{
	Position currentPosition = {7, 7};
	Bishop bishop(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x40201008040201);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(BishopGenerateAttacksTest, generateAttacks_Edge_Black)
{
	Position currentPosition = {0, 3};
	Bishop bishop(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8041221400);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(BishopGenerateAttacksTest, generateAttacks_Edge_White)
{
	Position currentPosition = {3, 0};
	Bishop bishop(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1008040200020408);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}