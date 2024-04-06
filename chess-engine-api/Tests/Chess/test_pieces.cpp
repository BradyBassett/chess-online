#include <gtest/gtest.h>
#include "../../Chess/models/Bishop.h"
#include "../../Chess/models/King.h"
#include "../../Chess/models/Knight.h"
#include "../../Chess/models/Pawn.h"
#include "../../Chess/models/Queen.h"
#include "../../Chess/models/Rook.h"

/*
! BISHOP TESTS
*/
TEST(BishopTest, generateAttacks_Center_Black)
{
	Bishop bishop(Color::Black, {3, 3});
	Bitboard expectedAttacks = Bitboard(0x8041221400142241);

	ASSERT_EQ(bishop.generateAttacks(), expectedAttacks);
}

TEST(BishopTest, generateAttacks_Center_White)
{
	Bishop bishop(Color::White, {4, 4});
	Bitboard expectedAttacks = Bitboard(0x8444280028448201);

	ASSERT_EQ(bishop.generateAttacks(), expectedAttacks);
}

TEST(BishopTest, generateAttacks_Corner_Black)
{
	Bishop bishop(Color::Black, {0, 0});
	Bitboard expectedAttacks = Bitboard(0x8040201008040200);

	ASSERT_EQ(bishop.generateAttacks(), expectedAttacks);
}

TEST(BishopTest, generateAttacks_Corner_White)
{
	Bishop bishop(Color::Black, {7, 7});
	Bitboard expectedAttacks = Bitboard(0x40201008040201);

	ASSERT_EQ(bishop.generateAttacks(), expectedAttacks);
}

TEST(BishopTest, generateAttacks_Edge_Black)
{
	Bishop bishop(Color::Black, {0, 3});
	Bitboard expectedAttacks = Bitboard(0x8041221400);

	ASSERT_EQ(bishop.generateAttacks(), expectedAttacks);
}

TEST(BishopTest, generateAttacks_Edge_White)
{
	Bishop bishop(Color::White, {3, 0});
	Bitboard expectedAttacks = Bitboard(0x1008040200020408);

	ASSERT_EQ(bishop.generateAttacks(), expectedAttacks);
}

/*
! KING TESTS
*/
TEST(KingTest, generateAttacks_Center_Black)
{
	King king(Color::Black, {3, 3});
	Bitboard expectedAttacks = Bitboard(0x1c141c0000);

	ASSERT_EQ(king.generateAttacks(), expectedAttacks);
}

TEST(KingTest, generateAttacks_Center_White)
{
	King king(Color::White, {4, 4});
	Bitboard expectedAttacks = Bitboard(0x382838000000);

	ASSERT_EQ(king.generateAttacks(), expectedAttacks);
}

TEST(KingTest, generateAttacks_Corner_Black)
{
	King king(Color::Black, {0, 0});
	Bitboard expectedAttacks = Bitboard(0x302);

	ASSERT_EQ(king.generateAttacks(), expectedAttacks);
}

TEST(KingTest, generateAttacks_Corner_White)
{
	King king(Color::White, {7, 7});
	Bitboard expectedAttacks = Bitboard(0x40c0000000000000);

	ASSERT_EQ(king.generateAttacks(), expectedAttacks);
}

TEST(KingTest, generateAttacks_Edge_Black)
{
	King king(Color::Black, {0, 3});
	Bitboard expectedAttacks = Bitboard(0x1c14);

	ASSERT_EQ(king.generateAttacks(), expectedAttacks);
}

TEST(KingTest, generateAttacks_Edge_White)
{
	King king(Color::White, {3, 0});
	Bitboard expectedAttacks = Bitboard(0x302030000);

	ASSERT_EQ(king.generateAttacks(), expectedAttacks);
}

TEST(KingTest, getPotentialMoves_Center_CanNotCastle)
{
	King king(Color::White, {4, 4});
	king.setCanCastleKingside(false);
	king.setCanCastleQueenside(false);

	Bitboard expectedMoves = Bitboard(0x382838000000);

	ASSERT_EQ(king.getPotentialMoves(), expectedMoves);
}

TEST(KingTest, getPotentialMoves_White_Starting_Position_CanCastleKingside)
{
	King king(Color::White, {7, 4});
	king.setCanCastleKingside(true);
	king.setCanCastleQueenside(false);

	Bitboard expectedMoves = Bitboard(0x6838000000000000);

	ASSERT_EQ(king.getPotentialMoves(), expectedMoves);
}

TEST(KingTest, getPotentialMoves_White_Starting_Position_CanCastleKingside_CanCastleQueenSide)
{
	King king(Color::White, {7, 4});
	king.setCanCastleKingside(true);
	king.setCanCastleQueenside(true);

	Bitboard expectedMoves = Bitboard(0x6c38000000000000);

	ASSERT_EQ(king.getPotentialMoves(), expectedMoves);
}

TEST(KingTest, getPotentialMoves_Black_Starting_Position_CanCastleQueenSide)
{
	King king(Color::White, {0, 4});
	king.setCanCastleKingside(false);
	king.setCanCastleQueenside(true);

	Bitboard expectedMoves = Bitboard(0x382c);

	ASSERT_EQ(king.getPotentialMoves(), expectedMoves);
}

TEST(KingTest, getPotentialMoves_Black_Starting_Position_CanCastleKingside_CanCastleQueenSide)
{
	King king(Color::White, {0, 4});
	king.setCanCastleKingside(true);
	king.setCanCastleQueenside(true);

	Bitboard expectedMoves = Bitboard(0x386c);

	ASSERT_EQ(king.getPotentialMoves(), expectedMoves);
}

/*
! KNIGHT TESTS
*/
TEST(KnightTest, generateAttacks_Center_Black)
{
	Knight knight(Color::Black, {3, 3});
	Bitboard expectedAttacks = Bitboard(0x142200221400);

	ASSERT_EQ(knight.generateAttacks(), expectedAttacks);
}

TEST(KnightTest, generateAttacks_Center_White)
{
	Knight knight(Color::White, {4, 4});
	Bitboard expectedAttacks = Bitboard(0x28440044280000);

	ASSERT_EQ(knight.generateAttacks(), expectedAttacks);
}

TEST(KnightTest, generateAttacks_Corner_Black)
{
	Knight knight(Color::Black, {0, 0});
	Bitboard expectedAttacks = Bitboard(0x20400);

	ASSERT_EQ(knight.generateAttacks(), expectedAttacks);
}

TEST(KnightTest, generateAttacks_Corner_White)
{
	Knight knight(Color::White, {7, 7});
	Bitboard expectedAttacks = Bitboard(0x20400000000000);

	ASSERT_EQ(knight.generateAttacks(), expectedAttacks);
}

TEST(KnightTest, generateAttacks_Edge_Black)
{
	Knight knight(Color::Black, {0, 3});
	Bitboard expectedAttacks = Bitboard(0x142200);

	ASSERT_EQ(knight.generateAttacks(), expectedAttacks);
}

TEST(KnightTest, generateAttacks_Edge_White)
{
	Knight knight(Color::White, {3, 0});
	Bitboard expectedAttacks = Bitboard(0x20400040200);

	ASSERT_EQ(knight.generateAttacks(), expectedAttacks);
}

/*
! PAWN TESTS
*/
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
	Pawn pawn(Color::Black, {3, 3});
	Bitboard expectedAttacks = Bitboard(0x1400000000);

	ASSERT_EQ(pawn.generateAttacks(), expectedAttacks);
}

TEST(PawnTest, generateAttacks_Center_White)
{
	Pawn pawn(Color::White, {4, 4});
	Bitboard expectedAttacks = Bitboard(0x28000000);

	ASSERT_EQ(pawn.generateAttacks(), expectedAttacks);
}

TEST(PawnTest, GenerateAttacks_Edge_Black)
{
	Pawn pawn(Color::Black, {3, 0});
	Bitboard expectedAttacks = Bitboard(0x200000000);

	ASSERT_EQ(pawn.generateAttacks(), expectedAttacks);
}

TEST(PawnTest, GenerateAttacks_Edge_White)
{
	Pawn pawn(Color::White, {5, 7});
	Bitboard expectedAttacks = Bitboard(0x4000000000);

	ASSERT_EQ(pawn.generateAttacks(), expectedAttacks);
}

TEST(PawnTest, GetPotentialMoves_WhitePawnHasNotMoved)
{
	Pawn pawn(Color::White, {1, 4});
	pawn.setHasMoved(false);
	Bitboard expectedMoves = Bitboard(0x381000000000);

	ASSERT_EQ(pawn.getPotentialMoves(), expectedMoves);
}

TEST(PawnTest, GetPotentialMoves_BlackPawnHasNotMoved)
{
	Pawn pawn(Color::Black, {1, 3});
	pawn.setHasMoved(false);
	Bitboard expectedMoves = Bitboard(0x10380000);

	ASSERT_EQ(pawn.getPotentialMoves(), expectedMoves);
}

TEST(PawnTest, GetPotentialMoves_WhitePawnMoved)
{
	Pawn pawn(Color::White, {4, 4});
	pawn.setHasMoved(true);
	Bitboard expectedMoves = Bitboard(0x38000000);

	ASSERT_EQ(pawn.getPotentialMoves(), expectedMoves);
}

TEST(PawnTest, GetPotentialMoves_BlackPawnMoved)
{
	Pawn pawn(Color::Black, {1, 3});
	pawn.setHasMoved(true);
	Bitboard expectedMoves = Bitboard(0x3800000000);

	ASSERT_EQ(pawn.getPotentialMoves(), expectedMoves);
}

/*
! QUEEN TESTS
*/
TEST(QueenTest, generateAttacks_Center_Black)
{
	Queen queen(Color::Black, {3, 3});
	Bitboard expectedAttacks = Bitboard(0x88492a1cf71c2a49);

	ASSERT_EQ(queen.generateAttacks(), expectedAttacks);
}

TEST(QueenTest, generateAttacks_Center_White)
{
	Queen queen(Color::White, {4, 4});
	Bitboard expectedAttacks = Bitboard(0x925438ef38549211);

	ASSERT_EQ(queen.generateAttacks(), expectedAttacks);
}

TEST(QueenTest, generateAttacks_Corner_Black)
{
	Queen queen(Color::Black, {0, 0});
	Bitboard expectedAttacks = Bitboard(0x81412111090503fe);

	ASSERT_EQ(queen.generateAttacks(), expectedAttacks);
}

TEST(QueenTest, generateAttacks_Corner_White)
{
	Queen queen(Color::Black, {7, 7});
	Bitboard expectedAttacks = Bitboard(0x7fc0a09088848281);

	ASSERT_EQ(queen.generateAttacks(), expectedAttacks);
}

TEST(QueenTest, generateAttacks_Edge_Black)
{
	Queen queen(Color::Black, {0, 3});
	Bitboard expectedAttacks = Bitboard(0x8080888492a1cf7);

	ASSERT_EQ(queen.generateAttacks(), expectedAttacks);
}

TEST(QueenTest, generateAttacks_Edge_White)
{
	Queen queen(Color::White, {3, 0});
	Bitboard expectedAttacks = Bitboard(0x11090503fe030509);

	ASSERT_EQ(queen.generateAttacks(), expectedAttacks);
}

/*
! ROOK TESTS
*/
TEST(RookTest, generateAttacks_Center_Black)
{
	Rook rook(Color::Black, {3, 3});
	Bitboard expectedAttacks = Bitboard(0x8080808f7080808);

	ASSERT_EQ(rook.generateAttacks(), expectedAttacks);
}

TEST(RookTest, generateAttacks_Center_White)
{
	Rook rook(Color::White, {4, 4});
	Bitboard expectedAttacks = Bitboard(0x101010ef10101010);

	ASSERT_EQ(rook.generateAttacks(), expectedAttacks);
}

TEST(RookTest, generateAttacks_Corner_Black)
{
	Rook rook(Color::Black, {0, 0});
	Bitboard expectedAttacks = Bitboard(0x1010101010101fe);

	ASSERT_EQ(rook.generateAttacks(), expectedAttacks);
}

TEST(RookTest, generateAttacks_Corner_White)
{
	Rook rook(Color::Black, {7, 7});
	Bitboard expectedAttacks = Bitboard(0x7f80808080808080);

	ASSERT_EQ(rook.generateAttacks(), expectedAttacks);
}

TEST(RookTest, generateAttacks_Edge_Black)
{
	Rook rook(Color::Black, {0, 3});
	Bitboard expectedAttacks = Bitboard(0x8080808080808f7);

	ASSERT_EQ(rook.generateAttacks(), expectedAttacks);
}

TEST(RookTest, generateAttacks_Edge_White)
{
	Rook rook(Color::White, {3, 0});
	Bitboard expectedAttacks = Bitboard(0x1010101fe010101);

	ASSERT_EQ(rook.generateAttacks(), expectedAttacks);
}
