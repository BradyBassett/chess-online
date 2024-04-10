#include "KingGetPotentialMovesTest.hpp"

TEST_F(KingGetPotentialMovesTest, getPotentialMoves_Center_CanNotCastle)
{
	Position currentPosition = {4, 4};
	King king(Color::White, currentPosition);

	king.setCanCastleKingside(false);
	king.setCanCastleQueenside(false);

	Bitboard expectedMoves = Bitboard(0x382838000000);
	Bitboard actualMoves = king.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST_F(KingGetPotentialMovesTest, getPotentialMoves_White_Starting_Position_CanCastleKingside)
{
	Position currentPosition = {7, 4};
	King king(Color::White, currentPosition);

	king.setCanCastleKingside(true);
	king.setCanCastleQueenside(false);

	Bitboard expectedMoves = Bitboard(0x6838000000000000);
	Bitboard actualMoves = king.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST_F(KingGetPotentialMovesTest, getPotentialMoves_White_Starting_Position_CanCastleKingside_CanCastleQueenSide)
{
	Position currentPosition = {7, 4};
	King king(Color::White, currentPosition);

	king.setCanCastleKingside(true);
	king.setCanCastleQueenside(true);

	Bitboard expectedMoves = Bitboard(0x6c38000000000000);
	Bitboard actualMoves = king.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST_F(KingGetPotentialMovesTest, getPotentialMoves_Black_Starting_Position_CanCastleQueenSide)
{
	Position currentPosition = {0, 4};
	King king(Color::White, currentPosition);

	king.setCanCastleKingside(false);
	king.setCanCastleQueenside(true);

	Bitboard expectedMoves = Bitboard(0x382c);
	Bitboard actualMoves = king.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST_F(KingGetPotentialMovesTest, getPotentialMoves_Black_Starting_Position_CanCastleKingside_CanCastleQueenSide)
{
	Position currentPosition = {0, 4};
	King king(Color::White, currentPosition);

	king.setCanCastleKingside(true);
	king.setCanCastleQueenside(true);

	Bitboard expectedMoves = Bitboard(0x386c);
	Bitboard actualMoves = king.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}