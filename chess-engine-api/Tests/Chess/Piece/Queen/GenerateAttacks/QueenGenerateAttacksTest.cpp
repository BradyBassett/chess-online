#include "QueenGenerateAttacksTest.hpp"

TEST_F(QueenGenerateAttacksTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	Queen queen(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x88492a1cf71c2a49);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(QueenGenerateAttacksTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	Queen queen(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x925438ef38549211);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(QueenGenerateAttacksTest, generateAttacks_Corner_Black)
{
	Position currentPosition = {0, 0};
	Queen queen(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x81412111090503fe);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(QueenGenerateAttacksTest, generateAttacks_Corner_White)
{
	Position currentPosition = {7, 7};
	Queen queen(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x7fc0a09088848281);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(QueenGenerateAttacksTest, generateAttacks_Edge_Black)
{
	Position currentPosition = {0, 3};
	Queen queen(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8080888492a1cf7);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST_F(QueenGenerateAttacksTest, generateAttacks_Edge_White)
{
	Position currentPosition = {3, 0};
	Queen queen(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x11090503fe030509);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}