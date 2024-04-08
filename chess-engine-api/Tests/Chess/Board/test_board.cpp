#include <gtest/gtest.h>
#include "../../../Chess/models/Board.h"

std::map<PieceType, std::string>
	pieceTypeMap =
		{
			{PieceType::Pawn, "Pawn"},
			{PieceType::Knight, "Knight"},
			{PieceType::Bishop, "Bishop"},
			{PieceType::Rook, "Rook"},
			{PieceType::Queen, "Queen"},
			{PieceType::King, "King"}};

std::map<Color, std::string> colorMap = {
	{Color::White, "White"},
	{Color::Black, "Black"}};

void validatePieceCount(Board &board, std::array<int, 6> pieceCounts)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			Color color = static_cast<Color>(i);
			PieceType pieceType = static_cast<PieceType>(j);

			ASSERT_EQ(board.getPieceCount(color, pieceType), pieceCounts[j]) << "Color: " << colorMap[color] << " PieceType: " << pieceTypeMap[pieceType];
		}
	}
}

void validatePiecePositions(Board &board, std::array<std::optional<PieceType>, 64> expectedPieceTypes)
{
	for (int i = 0; i < 64; i++)
	{
		if (!expectedPieceTypes[i].has_value())
		{
			ASSERT_EQ(board.getSquare(i).getPiece(), nullptr) << "Square: " << i;
		}
		else
		{
			ASSERT_EQ(board.getSquare(i).getPiece()->getPieceType(), *expectedPieceTypes[i]) << "Square: " << i;
		}
	}
}

void validateBitboards(Board &board, std::array<std::array<Bitboard, 6>, 2> expectedBitboards)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			Color color = static_cast<Color>(i);
			PieceType pieceType = static_cast<PieceType>(j);
			Bitboard bitboard = board.getBitboard(color, pieceType);

			ASSERT_EQ(bitboard.getValue(), expectedBitboards[i][j].getValue()) << "Color: " << colorMap[color] << " PieceType: " << pieceTypeMap[pieceType];
		}
	}
}

void validateWhitePawnAttackTable(Board &board)
{
	for (int i = 0; i < 64; i++)
	{
		uint64_t expectedValue = 0;
		if (i % 8 != 0 && i > 7) // not on 'a' file and not on the 1st rank
		{
			expectedValue |= 1ULL << (i - 9);
		}
		if (i % 8 != 7 && i > 7) // not on 'h' file and not on the 1st rank
		{
			expectedValue |= 1ULL << (i - 7);
		}

		ASSERT_EQ(board.getAttackTable(Color::White, PieceType::Pawn)[i].getValue(), expectedValue);
	}
}

void validateBlackPawnAttackTable(Board &board)
{
	for (int i = 0; i < 64; i++)
	{
		uint64_t expectedValue = 0;
		if (i % 8 != 7 && i < 55) // not on 'h' file and not on the 7th or 8th rank
		{
			expectedValue |= 1ULL << (i + 9);
		}
		if (i % 8 != 0 && i < 56) // not on 'a' file and not on the 8th rank
		{
			expectedValue |= 1ULL << (i + 7);
		}

		ASSERT_EQ(board.getAttackTable(Color::Black, PieceType::Pawn)[i].getValue(), expectedValue) << "Square: " << i;
	}
}

void validateKnightAttackTable(Board &board)
{
	for (int i = 0; i < 64; i++)
	{
		uint64_t expectedValue = 0;
		if (i % 8 < 6 && i / 8 < 7)
		{ // can move 2 right and 1 up
			expectedValue |= 1ULL << (i + 10);
		}
		if (i % 8 < 7 && i / 8 < 6)
		{ // can move 1 right and 2 up
			expectedValue |= 1ULL << (i + 17);
		}
		if (i % 8 < 7 && i / 8 > 1)
		{ // can move 1 right and 2 down
			expectedValue |= 1ULL << (i - 15);
		}
		if (i % 8 < 6 && i / 8 > 0)
		{ // can move 2 right and 1 down
			expectedValue |= 1ULL << (i - 6);
		}
		if (i % 8 > 1 && i / 8 > 0)
		{ // can move 2 left and 1 down
			expectedValue |= 1ULL << (i - 10);
		}
		if (i % 8 > 0 && i / 8 > 1)
		{ // can move 1 left and 2 down
			expectedValue |= 1ULL << (i - 17);
		}
		if (i % 8 > 0 && i / 8 < 6)
		{ // can move 1 left and 2 up
			expectedValue |= 1ULL << (i + 15);
		}
		if (i % 8 > 1 && i / 8 < 7)
		{ // can move 2 left and 1 up
			expectedValue |= 1ULL << (i + 6);
		}

		// White selected here but the attack table is the same for both colors
		ASSERT_EQ(board.getAttackTable(Color::White, PieceType::Knight)[i].getValue(), expectedValue);
	}
}

uint64_t calculateBishopExpectedValue(int i)
{
	uint64_t expectedValue = 0;
	for (int j = 1; i % 8 + j < 8 && i / 8 + j < 8; j++)
	{ // can move diagonally up-right
		expectedValue |= 1ULL << (i + 9 * j);
	}
	for (int j = 1; i % 8 + j < 8 && i / 8 - j >= 0; j++)
	{ // can move diagonally down-right
		expectedValue |= 1ULL << (i - 7 * j);
	}
	for (int j = 1; i % 8 - j >= 0 && i / 8 + j < 8; j++)
	{ // can move diagonally up-left
		expectedValue |= 1ULL << (i + 7 * j);
	}
	for (int j = 1; i % 8 - j >= 0 && i / 8 - j >= 0; j++)
	{ // can move diagonally down-left
		expectedValue |= 1ULL << (i - 9 * j);
	}
	return expectedValue;
}

void validateBishopAttackTable(Board &board)
{
	for (int i = 0; i < 64; i++)
	{
		uint64_t expectedValue = calculateBishopExpectedValue(i);

		// White selected here but the attack table is the same for both colors
		ASSERT_EQ(board.getAttackTable(Color::White, PieceType::Bishop)[i].getValue(), expectedValue);
	}
}

uint64_t calculateRookExpectedValue(int i)
{
	uint64_t expectedValue = 0;
	for (int j = 1; i % 8 + j < 8; j++)
	{ // can move right
		expectedValue |= 1ULL << (i + j);
	}
	for (int j = 1; i % 8 - j >= 0; j++)
	{ // can move left
		expectedValue |= 1ULL << (i - j);
	}
	for (int j = 1; i / 8 + j < 8; j++)
	{ // can move up
		expectedValue |= 1ULL << (i + 8 * j);
	}
	for (int j = 1; i / 8 - j >= 0; j++)
	{ // can move down
		expectedValue |= 1ULL << (i - 8 * j);
	}
	return expectedValue;
}

void validateRookAttackTable(Board &board)
{
	for (int i = 0; i < 64; i++)
	{
		uint64_t expectedValue = calculateRookExpectedValue(i);

		// White selected here but the attack table is the same for both colors
		ASSERT_EQ(board.getAttackTable(Color::White, PieceType::Rook)[i].getValue(), expectedValue);
	}
}

void validateQueenAttackTable(Board &board)
{
	for (int i = 0; i < 64; i++)
	{
		uint64_t expectedRookValue = calculateRookExpectedValue(i);
		uint64_t expectedBishopValue = calculateBishopExpectedValue(i);
		uint64_t expectedValue = expectedRookValue | expectedBishopValue;

		// White selected here but the attack table is the same for both colors
		ASSERT_EQ(board.getAttackTable(Color::White, PieceType::Queen)[i].getValue(), expectedValue);
	}
}

void validateKingAttackTable(Board &board)
{
	for (int i = 0; i < 64; i++)
	{
		uint64_t expectedValue = 0;
		if (i % 8 + 1 < 8)
		{ // can move right
			expectedValue |= 1ULL << (i + 1);
		}
		if (i % 8 - 1 >= 0)
		{ // can move left
			expectedValue |= 1ULL << (i - 1);
		}
		if (i / 8 + 1 < 8)
		{ // can move up
			expectedValue |= 1ULL << (i + 8);
		}
		if (i / 8 - 1 >= 0)
		{ // can move down
			expectedValue |= 1ULL << (i - 8);
		}
		if (i % 8 + 1 < 8 && i / 8 + 1 < 8)
		{ // can move diagonally up-right
			expectedValue |= 1ULL << (i + 9);
		}
		if (i % 8 + 1 < 8 && i / 8 - 1 >= 0)
		{ // can move diagonally down-right
			expectedValue |= 1ULL << (i - 7);
		}
		if (i % 8 - 1 >= 0 && i / 8 + 1 < 8)
		{ // can move diagonally up-left
			expectedValue |= 1ULL << (i + 7);
		}
		if (i % 8 - 1 >= 0 && i / 8 - 1 >= 0)
		{ // can move diagonally down-left
			expectedValue |= 1ULL << (i - 9);
		}

		// White selected here but the attack table is the same for both colors
		ASSERT_EQ(board.getAttackTable(Color::White, PieceType::King)[i].getValue(), expectedValue);
	}
}

TEST(BoardConstructorTest, DefaultConstructor)
{
	Board board = Board();

	// validate squares
	ASSERT_EQ(board.getSquares().size() * board.getSquares()[0].size(), 64);

	// validate rooks
	ASSERT_EQ(board.getRooks().size(), 4);

	// validate kings
	ASSERT_EQ(board.getKings().size(), 2);

	// validate piece counts
	std::array<int, 6> pieceCounts = {8, 2, 2, 2, 1, 1}; // pawns, knights, bishops, rooks, queens, king
	validatePieceCount(board, pieceCounts);

	// validate piece positions
	std::array<std::optional<PieceType>, 64> expectedPieceTypes = {
		PieceType::Rook, PieceType::Knight, PieceType::Bishop, PieceType::Queen, PieceType::King, PieceType::Bishop, PieceType::Knight, PieceType::Rook,
		PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn,
		std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
		std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
		std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
		std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
		PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn,
		PieceType::Rook, PieceType::Knight, PieceType::Bishop, PieceType::Queen, PieceType::King, PieceType::Bishop, PieceType::Knight, PieceType::Rook};
	validatePiecePositions(board, expectedPieceTypes);

	// validate bitboards
	std::array<std::array<Bitboard, 6>, 2> expectedBitboards = {
		{{{Bitboard(0xff000000000000), Bitboard(0x4200000000000000), Bitboard(0x2400000000000000), Bitboard(0x8100000000000000), Bitboard(0x800000000000000), Bitboard(0x1000000000000000)}},
		 {{Bitboard(0xff00), Bitboard(0x42), Bitboard(0x24), Bitboard(0x81), Bitboard(0x8), Bitboard(0x10)}}}};
	validateBitboards(board, expectedBitboards);

	// Validate Attack Tables
	validateWhitePawnAttackTable(board);
	validateBlackPawnAttackTable(board);
	validateKnightAttackTable(board);
	validateBishopAttackTable(board);
	validateRookAttackTable(board);
	validateQueenAttackTable(board);
	validateKingAttackTable(board);

	ASSERT_TRUE(board.getCanCastleKingside(Color::White));
	ASSERT_TRUE(board.getCanCastleKingside(Color::Black));
	ASSERT_TRUE(board.getCanCastleQueenside(Color::White));
	ASSERT_TRUE(board.getCanCastleQueenside(Color::Black));

	// validate en passant target square
	ASSERT_EQ(board.getEnPassantTargetSquare(), nullptr);
}

TEST(BoardConstructorTest, DefaultConstructor)
{
	Board board = Board();

	// validate squares
	ASSERT_EQ(board.getSquares().size() * board.getSquares()[0].size(), 64);

	// validate rooks
	ASSERT_EQ(board.getRooks().size(), 4);

	// validate kings
	ASSERT_EQ(board.getKings().size(), 2);

	// validate piece counts
	std::array<int, 6> pieceCounts = {8, 2, 2, 2, 1, 1}; // pawns, knights, bishops, rooks, queens, king
	validatePieceCount(board, pieceCounts);

	// validate piece positions
	std::array<std::optional<PieceType>, 64> expectedPieceTypes = {
		PieceType::Rook, PieceType::Knight, PieceType::Bishop, PieceType::Queen, PieceType::King, PieceType::Bishop, PieceType::Knight, PieceType::Rook,
		PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn,
		std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
		std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
		std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
		std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
		PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn,
		PieceType::Rook, PieceType::Knight, PieceType::Bishop, PieceType::Queen, PieceType::King, PieceType::Bishop, PieceType::Knight, PieceType::Rook};
	validatePiecePositions(board, expectedPieceTypes);

	// validate bitboards
	std::array<std::array<Bitboard, 6>, 2> expectedBitboards = {
		{{{Bitboard(0xff000000000000), Bitboard(0x4200000000000000), Bitboard(0x2400000000000000), Bitboard(0x8100000000000000), Bitboard(0x800000000000000), Bitboard(0x1000000000000000)}},
		 {{Bitboard(0xff00), Bitboard(0x42), Bitboard(0x24), Bitboard(0x81), Bitboard(0x8), Bitboard(0x10)}}}};
	validateBitboards(board, expectedBitboards);

	// Validate Attack Tables
	validateWhitePawnAttackTable(board);
	validateBlackPawnAttackTable(board);
	validateKnightAttackTable(board);
	validateBishopAttackTable(board);
	validateRookAttackTable(board);
	validateQueenAttackTable(board);
	validateKingAttackTable(board);

	ASSERT_TRUE(board.getCanCastleKingside(Color::White));
	ASSERT_TRUE(board.getCanCastleKingside(Color::Black));
	ASSERT_TRUE(board.getCanCastleQueenside(Color::White));
	ASSERT_TRUE(board.getCanCastleQueenside(Color::Black));

	// validate en passant target square
	ASSERT_EQ(board.getEnPassantTargetSquare(), nullptr);
}