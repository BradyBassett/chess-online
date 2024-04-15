#include "QueenGenerateAttacksTest.hpp"

QueenGenerateAttacksTest::QueenGenerateAttacksTest() : param(GetParam().second) {}

TEST_P(QueenGenerateAttacksTest, generateAttacks) {
    Queen queen(param.color, param.currentPosition);
    Bitboard actualAttacks = queen.generateAttacks();
    Bitboard expectedAttacks = Bitboard(param.expectedAttacks);

    ASSERT_EQ(actualAttacks, expectedAttacks);
}

std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> QueenGenerateAttacksTest::testCases = {
    {"Center_Black", PieceGenerateAttacksTestParam{{3, 3}, Color::Black, 0x88492a1cf71c2a49}},
    {"Center_White", PieceGenerateAttacksTestParam{{4, 4}, Color::White, 0x925438ef38549211}},
    {"Corner_Black", PieceGenerateAttacksTestParam{{0, 0}, Color::Black, 0x81412111090503fe}},
    {"Corner_White", PieceGenerateAttacksTestParam{{7, 7}, Color::White, 0x7fc0a09088848281}},
    {"Edge_Black", PieceGenerateAttacksTestParam{{0, 3}, Color::White, 0x8080888492a1cf7}},
    {"Edge_White", PieceGenerateAttacksTestParam{{3, 0}, Color::White, 0x11090503fe030509}}
};

INSTANTIATE_TEST_SUITE_P(
    QueenGenerateAttacks,
    QueenGenerateAttacksTest,
    ::testing::ValuesIn(QueenGenerateAttacksTest::testCases),
	[](const testing::TestParamInfo<QueenGenerateAttacksTest::ParamType>& info) {
		return info.param.first;
	}
);