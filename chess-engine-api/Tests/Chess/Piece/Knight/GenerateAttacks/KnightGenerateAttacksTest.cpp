#include "KnightGenerateAttacksTest.hpp"

KnightGenerateAttacksTest::KnightGenerateAttacksTest() : param(GetParam().second) {}

TEST_P(KnightGenerateAttacksTest, generateAttacks) {
    Knight knight(param.color, param.currentPosition);
    Bitboard actualAttacks = knight.generateAttacks();
    Bitboard expectedAttacks = Bitboard(param.expectedAttacks);

    ASSERT_EQ(actualAttacks, expectedAttacks);
}

std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> KnightGenerateAttacksTest::testCases = {
    {"Center_Black", PieceGenerateAttacksTestParam{{3, 3}, Color::Black, 0x142200221400}},
    {"Center_White", PieceGenerateAttacksTestParam{{4, 4}, Color::White, 0x28440044280000}},
    {"Corner_Black", PieceGenerateAttacksTestParam{{0, 0}, Color::Black, 0x20400}},
    {"Corner_White", PieceGenerateAttacksTestParam{{7, 7}, Color::White, 0x20400000000000}},
    {"Edge_Black", PieceGenerateAttacksTestParam{{0, 3}, Color::White, 0x142200}},
    {"Edge_White", PieceGenerateAttacksTestParam{{3, 0}, Color::White, 0x20400040200}}
};

INSTANTIATE_TEST_SUITE_P(
    KnightGenerateAttacks,
    KnightGenerateAttacksTest,
    ::testing::ValuesIn(KnightGenerateAttacksTest::testCases),
	[](const testing::TestParamInfo<KnightGenerateAttacksTest::ParamType>& info) {
		return info.param.first;
	}
);
