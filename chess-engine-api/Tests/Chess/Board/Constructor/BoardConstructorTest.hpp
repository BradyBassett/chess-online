#ifndef BOARDCONSTRUCTORTEST_HPP
#define BOARDCONSTRUCTORTEST_HPP

#include "../BoardTest.hpp"

struct BoardConstructorTestParams
{
	std::string fenPosition;
	std::string castlingAvaliability;
	std::string enPassantTarget;
	int expectedRookCount;
	int expectedKingCount;
	std::array<std::array<int, 6>, 2> expectedPieceCounts;
	std::array<std::optional<PieceType>, 64> expectedPieceTypes;
	std::array<std::array<Bitboard, 6>, 2> expectedBitboards;
	Square *expectedEnPassantTargetSquare;
};

class BoardConstructorTest : public BoardTest, public ::testing::TestWithParam<std::pair<std::string, BoardConstructorTestParams>>
{
private:

protected:
	BoardConstructorTestParams param;

	void validatePieceCount(Board &board, std::array<std::array<int, 6>, 2> pieceCounts);

	void validatePiecePositions(Board &board, std::array<std::optional<PieceType>, 64> expectedPieceTypes);

	void validateBitboards(Board &board, std::array<std::array<Bitboard, 6>, 2> expectedBitboards);

	void validateWhitePawnAttackTable(Board &board);

	void validateBlackPawnAttackTable(Board &board);

	void validateKnightAttackTable(Board &board);

	uint64_t calculateBishopExpectedValue(int i);

	void validateBishopAttackTable(Board &board);

	uint64_t calculateRookExpectedValue(int i);

	void validateRookAttackTable(Board &board);

	void validateQueenAttackTable(Board &board);

	void validateKingAttackTable(Board &board);

public:
	BoardConstructorTest();
	static std::vector<std::pair<std::string, BoardConstructorTestParams>> testCases;
};

#endif // BOARDCONSTRUCTORTEST_HPP