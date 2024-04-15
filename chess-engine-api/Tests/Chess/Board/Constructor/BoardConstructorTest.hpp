#ifndef BOARDCONSTRUCTORTEST_HPP
#define BOARDCONSTRUCTORTEST_HPP

#include "../BoardTest.hpp"

class BoardConstructorTest : public BoardTest
{
private:

protected:
	void validatePieceCount(Board &board, std::array<int, 6> pieceCounts);

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
};

#endif // BOARDCONSTRUCTORTEST_HPP