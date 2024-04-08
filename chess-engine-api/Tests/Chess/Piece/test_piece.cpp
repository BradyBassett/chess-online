#include <gtest/gtest.h>
#include "../../Chess/models/Bishop.h"
#include "../../Chess/models/King.h"
#include "../../Chess/models/Knight.h"
#include "../../Chess/models/Pawn.h"
#include "../../Chess/models/Queen.h"
#include "../../Chess/models/Rook.h"

// ! BISHOP TESTS
TEST(BishopTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	Bishop bishop(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8041221400142241);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(BishopTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	Bishop bishop(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8244280028448201);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(BishopTest, generateAttacks_Corner_Black)
{
	Position currentPosition = {0, 0};
	Bishop bishop(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8040201008040200);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(BishopTest, generateAttacks_Corner_White)
{
	Position currentPosition = {7, 7};
	Bishop bishop(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x40201008040201);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(BishopTest, generateAttacks_Edge_Black)
{
	Position currentPosition = {0, 3};
	Bishop bishop(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8041221400);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(BishopTest, generateAttacks_Edge_White)
{
	Position currentPosition = {3, 0};
	Bishop bishop(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1008040200020408);
	Bitboard actualAttacks = bishop.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

// ! KING TESTS
TEST(KingTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	King king(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1c141c0000);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KingTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	King king(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x382838000000);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KingTest, generateAttacks_Corner_Black)
{
	Position currentPosition = {0, 0};
	King king(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x302);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KingTest, generateAttacks_Corner_White)
{
	Position currentPosition = {7, 7};
	King king(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x40c0000000000000);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KingTest, generateAttacks_Edge_Black)
{
	Position currentPosition = {0, 3};
	King king(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1c14);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KingTest, generateAttacks_Edge_White)
{
	Position currentPosition = {3, 0};
	King king(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x302030000);
	Bitboard actualAttacks = king.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KingTest, getPotentialMoves_Center_CanNotCastle)
{
	Position currentPosition = {4, 4};
	King king(Color::White, currentPosition);

	king.setCanCastleKingside(false);
	king.setCanCastleQueenside(false);

	Bitboard expectedMoves = Bitboard(0x382838000000);
	Bitboard actualMoves = king.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST(KingTest, getPotentialMoves_White_Starting_Position_CanCastleKingside)
{
	Position currentPosition = {7, 4};
	King king(Color::White, currentPosition);

	king.setCanCastleKingside(true);
	king.setCanCastleQueenside(false);

	Bitboard expectedMoves = Bitboard(0x6838000000000000);
	Bitboard actualMoves = king.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST(KingTest, getPotentialMoves_White_Starting_Position_CanCastleKingside_CanCastleQueenSide)
{
	Position currentPosition = {7, 4};
	King king(Color::White, currentPosition);

	king.setCanCastleKingside(true);
	king.setCanCastleQueenside(true);

	Bitboard expectedMoves = Bitboard(0x6c38000000000000);
	Bitboard actualMoves = king.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST(KingTest, getPotentialMoves_Black_Starting_Position_CanCastleQueenSide)
{
	Position currentPosition = {0, 4};
	King king(Color::White, currentPosition);

	king.setCanCastleKingside(false);
	king.setCanCastleQueenside(true);

	Bitboard expectedMoves = Bitboard(0x382c);
	Bitboard actualMoves = king.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST(KingTest, getPotentialMoves_Black_Starting_Position_CanCastleKingside_CanCastleQueenSide)
{
	Position currentPosition = {0, 4};
	King king(Color::White, currentPosition);

	king.setCanCastleKingside(true);
	king.setCanCastleQueenside(true);

	Bitboard expectedMoves = Bitboard(0x386c);
	Bitboard actualMoves = king.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

// ! KNIGHT TESTS
TEST(KnightTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	Knight knight(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x142200221400);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KnightTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	Knight knight(Color::White, currentPosition);
	Bitboard expectedAttacks = Bitboard(0x28440044280000);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KnightTest, generateAttacks_Corner_Black)
{
	Position currentPosition = {0, 0};
	Knight knight(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x20400);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KnightTest, generateAttacks_Corner_White)
{
	Position currentPosition = {7, 7};
	Knight knight(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x20400000000000);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KnightTest, generateAttacks_Edge_Black)
{
	Position currentPosition = {0, 3};
	Knight knight(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x142200);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(KnightTest, generateAttacks_Edge_White)
{
	Position currentPosition = {3, 0};
	Knight knight(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x20400040200);
	Bitboard actualAttacks = knight.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

// ! PAWN TESTS
TEST(PawnTest, CanMoveOneSquare_ValidMove_White)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {1, 3};
	Pawn pawn(Color::White, currentPosition);

	bool result = pawn.canMoveOneSquare(targetPosition);

	ASSERT_TRUE(result);
}

TEST(PawnTest, CanMoveOneSquare_ValidMove_Black)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {3, 3};
	Pawn pawn(Color::Black, currentPosition);

	bool result = pawn.canMoveOneSquare(targetPosition);

	ASSERT_TRUE(result);
}

TEST(PawnTest, CanMoveOneSquare_InvalidMove_White)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {0, 3};
	Pawn pawn(Color::White, currentPosition);

	bool result = pawn.canMoveOneSquare(targetPosition);

	ASSERT_FALSE(result);
}

TEST(PawnTest, CanMoveOneSquare_InvalidMove_Black)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {4, 3};
	Pawn pawn(Color::Black, currentPosition);

	bool result = pawn.canMoveOneSquare(targetPosition);

	ASSERT_FALSE(result);
}

TEST(PawnTest, CanMoveTwoSquares_ValidMove_White)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {0, 3};
	Pawn pawn(Color::White, currentPosition);

	bool result = pawn.canMoveTwoSquares(targetPosition);

	ASSERT_TRUE(result);
}

TEST(PawnTest, CanMoveTwoSquares_ValidMove_Black)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {4, 3};
	Pawn pawn(Color::Black, currentPosition);

	bool result = pawn.canMoveTwoSquares(targetPosition);

	ASSERT_TRUE(result);
}

TEST(PawnTest, CanMoveTwoSquares_InvalidMove_White)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {1, 3};
	Pawn pawn(Color::White, currentPosition);

	bool result = pawn.canMoveTwoSquares(targetPosition);

	ASSERT_FALSE(result);
}

TEST(PawnTest, CanMoveTwoSquares_InvalidMove_Black)
{
	Position currentPosition = {2, 3};
	Position targetPosition = {3, 3};
	Pawn pawn(Color::Black, currentPosition);

	bool result = pawn.canMoveTwoSquares(targetPosition);

	ASSERT_FALSE(result);
}

TEST(PawnTest, CanPromote_WhitePawnOnLastRow)
{
	Position targetPosition = {0, 7};
	Pawn pawn(Color::White, targetPosition);

	ASSERT_TRUE(pawn.canPromote(targetPosition));
}

TEST(PawnTest, CanPromote_WhitePawnNotOnLastRow)
{
	Position targetPosition = {3, 4};
	Pawn pawn(Color::White, targetPosition);

	ASSERT_FALSE(pawn.canPromote(targetPosition));
}

TEST(PawnTest, CanPromote_BlackPawnOnLastRow)
{
	Position targetPosition = {7, 0};
	Pawn pawn(Color::Black, targetPosition);

	ASSERT_TRUE(pawn.canPromote(targetPosition));
}

TEST(PawnTest, CanPromote_BlackPawnNotOnLastRow)
{
	Position targetPosition = {2, 5};
	Pawn pawn(Color::Black, targetPosition);

	ASSERT_FALSE(pawn.canPromote(targetPosition));
}

TEST(PawnTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	Pawn pawn(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1400000000);
	Bitboard actualAttacks = pawn.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(PawnTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	Pawn pawn(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x28000000);
	Bitboard actualAttacks = pawn.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(PawnTest, GenerateAttacks_Edge_Black)
{
	Position currentPosition = {3, 0};
	Pawn pawn(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x200000000);
	Bitboard actualAttacks = pawn.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(PawnTest, GenerateAttacks_Edge_White)
{
	Position currentPosition = {5, 7};
	Pawn pawn(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x4000000000);
	Bitboard actualAttacks = pawn.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(PawnTest, GetPotentialMoves_WhitePawnHasNotMoved)
{
	Position currentPosition = {6, 4};
	Pawn pawn(Color::White, currentPosition);

	pawn.setHasMoved(false);

	Bitboard expectedMoves = Bitboard(0x381000000000);
	Bitboard actualMoves = pawn.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST(PawnTest, GetPotentialMoves_BlackPawnHasNotMoved)
{
	Position currentPosition = {1, 3};
	Pawn pawn(Color::Black, currentPosition);

	pawn.setHasMoved(false);

	Bitboard expectedMoves = Bitboard(0x81c0000);
	Bitboard actualMoves = pawn.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST(PawnTest, GetPotentialMoves_WhitePawnMoved)
{
	Position currentPosition = {4, 4};
	Pawn pawn(Color::White, currentPosition);

	pawn.setHasMoved(true);

	Bitboard expectedMoves = Bitboard(0x38000000);
	Bitboard actualMoves = pawn.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

TEST(PawnTest, GetPotentialMoves_BlackPawnMoved)
{
	Position currentPosition = {4, 4};
	Pawn pawn(Color::Black, currentPosition);

	pawn.setHasMoved(true);

	Bitboard expectedMoves = Bitboard(0x380000000000);
	Bitboard actualMoves = pawn.getPotentialMoves();

	ASSERT_EQ(actualMoves, expectedMoves);
}

// ! QUEEN TESTS
TEST(QueenTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	Queen queen(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x88492a1cf71c2a49);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(QueenTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	Queen queen(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x925438ef38549211);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(QueenTest, generateAttacks_Corner_Black)
{
	Position currentPosition = {0, 0};
	Queen queen(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x81412111090503fe);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(QueenTest, generateAttacks_Corner_White)
{
	Position currentPosition = {7, 7};
	Queen queen(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x7fc0a09088848281);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(QueenTest, generateAttacks_Edge_Black)
{
	Position currentPosition = {0, 3};
	Queen queen(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8080888492a1cf7);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(QueenTest, generateAttacks_Edge_White)
{
	Position currentPosition = {3, 0};
	Queen queen(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x11090503fe030509);
	Bitboard actualAttacks = queen.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

// ! ROOK TESTS
TEST(RookTest, generateAttacks_Center_Black)
{
	Position currentPosition = {3, 3};
	Rook rook(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8080808f7080808);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(RookTest, generateAttacks_Center_White)
{
	Position currentPosition = {4, 4};
	Rook rook(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x101010ef10101010);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(RookTest, generateAttacks_Corner_Black)
{
	Position currentPosition = {0, 0};
	Rook rook(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1010101010101fe);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(RookTest, generateAttacks_Corner_White)
{
	Position currentPosition = {7, 7};
	Rook rook(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x7f80808080808080);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(RookTest, generateAttacks_Edge_Black)
{
	Position currentPosition = {0, 3};
	Rook rook(Color::Black, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x8080808080808f7);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}

TEST(RookTest, generateAttacks_Edge_White)
{
	Position currentPosition = {3, 0};
	Rook rook(Color::White, currentPosition);

	Bitboard expectedAttacks = Bitboard(0x1010101fe010101);
	Bitboard actualAttacks = rook.generateAttacks();

	ASSERT_EQ(actualAttacks, expectedAttacks);
}
