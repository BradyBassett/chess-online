#include "PawnGenerateAttacksTest.hpp"

PawnGenerateAttacksTest::PawnGenerateAttacksTest() : param(GetParam().second) {}

TEST_P(PawnGenerateAttacksTest, generateAttacks) {
    Pawn pawn(param.color, param.currentPosition);
    Bitboard actualAttacks = pawn.generateAttacks();
    Bitboard expectedAttacks = Bitboard(param.expectedAttacks);

    ASSERT_EQ(actualAttacks, expectedAttacks);
}

std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> PawnGenerateAttacksTest::testCases = {
    {"Center_Black", PieceGenerateAttacksTestParam{{3, 3}, Color::Black, 0x1400000000}},
    {"Center_White", PieceGenerateAttacksTestParam{{4, 4}, Color::White, 0x28000000}},
    {"Edge_Black", PieceGenerateAttacksTestParam{{3, 0}, Color::Black, 0x200000000}},
    {"Edge_White", PieceGenerateAttacksTestParam{{5, 7}, Color::White, 0x4000000000}}
};

INSTANTIATE_TEST_SUITE_P(
    PawnGenerateAttacks,
    PawnGenerateAttacksTest,
    ::testing::ValuesIn(PawnGenerateAttacksTest::testCases),
	[](const testing::TestParamInfo<PawnGenerateAttacksTest::ParamType>& info) {
		return info.param.first;
	}
);
