#include "RookGenerateAttacksTest.hpp"

RookGenerateAttacksTest::RookGenerateAttacksTest() : param(GetParam().second) {}

TEST_P(RookGenerateAttacksTest, generateAttacks) {
    Rook rook(param.color, param.currentPosition);
    Bitboard actualAttacks = rook.generateAttacks();
    Bitboard expectedAttacks = Bitboard(param.expectedAttacks);

    ASSERT_EQ(actualAttacks, expectedAttacks);
}

std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> RookGenerateAttacksTest::testCases = {
    {"Center_Black", PieceGenerateAttacksTestParam{{3, 3}, Color::Black, 0x8080808f7080808}},
    {"Center_White", PieceGenerateAttacksTestParam{{4, 4}, Color::White, 0x101010ef10101010}},
    {"Corner_Black", PieceGenerateAttacksTestParam{{0, 0}, Color::Black, 0x1010101010101fe}},
    {"Corner_White", PieceGenerateAttacksTestParam{{7, 7}, Color::Black, 0x7f80808080808080}},
    {"Edge_Black", PieceGenerateAttacksTestParam{{0, 3}, Color::White, 0x8080808080808f7}},
    {"Edge_White", PieceGenerateAttacksTestParam{{3, 0}, Color::White, 0x1010101fe010101}}
};

INSTANTIATE_TEST_SUITE_P(
    RookGenerateAttacks,
    RookGenerateAttacksTest,
    ::testing::ValuesIn(RookGenerateAttacksTest::testCases),
	[](const testing::TestParamInfo<RookGenerateAttacksTest::ParamType>& info) {
		return info.param.first;
	}
);
