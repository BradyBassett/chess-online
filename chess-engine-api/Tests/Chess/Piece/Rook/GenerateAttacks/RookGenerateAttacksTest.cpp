#include "RookGenerateAttacksTest.hpp"

TEST_F(RookGenerateAttacksTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	Rook rook(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8080808f7080808);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(RookGenerateAttacksTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	Rook rook(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x101010ef10101010);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(RookGenerateAttacksTest, generateAttacks_Corner_Black)
{
	Position currentPosition = {0, 0};
	Rook rook(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1010101010101fe);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(RookGenerateAttacksTest, generateAttacks_Corner_White)
{
	Position currentPosition = {7, 7};
	Rook rook(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x7f80808080808080);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(RookGenerateAttacksTest, generateAttacks_Edge_Black)
{
	Position currentPosition = {0, 3};
	Rook rook(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8080808080808f7);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(RookGenerateAttacksTest, generateAttacks_Edge_White)
{
	Position currentPosition = {3, 0};
	Rook rook(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1010101fe010101);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}
