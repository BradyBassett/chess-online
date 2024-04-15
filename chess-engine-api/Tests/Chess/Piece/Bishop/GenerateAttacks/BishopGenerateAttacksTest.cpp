#include "BishopGenerateAttacksTest.hpp"

BishopGenerateAttacksTest::BishopGenerateAttacksTest() : param(GetParam().second) {}

TEST_P(BishopGenerateAttacksTest, generateAttacks) {
    Bishop bishop(param.color, param.currentPosition);
    Bitboard actualAttacks = bishop.generateAttacks();
    Bitboard expectedAttacks = Bitboard(param.expectedAttacks);

    ASSERT_EQ(actualAttacks, expectedAttacks);
}

std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> BishopGenerateAttacksTest::testCases = {
    {"Center_Black", PieceGenerateAttacksTestParam{{3, 3}, Color::Black, 0x8041221400142241}},
    {"Center_White", PieceGenerateAttacksTestParam{{4, 4}, Color::White, 0x8244280028448201}},
    {"Corner_Black", PieceGenerateAttacksTestParam{{0, 0}, Color::Black, 0x8040201008040200}},
    {"Corner_White", PieceGenerateAttacksTestParam{{7, 7}, Color::White, 0x40201008040201}},
    {"Edge_Black", PieceGenerateAttacksTestParam{{0, 3}, Color::White, 0x8041221400}},
    {"Edge_White", PieceGenerateAttacksTestParam{{3, 0}, Color::White, 0x1008040200020408}}
};

INSTANTIATE_TEST_SUITE_P(
    BishopGenerateAttacks,
    BishopGenerateAttacksTest,
    ::testing::ValuesIn(BishopGenerateAttacksTest::testCases),
	[](const testing::TestParamInfo<BishopGenerateAttacksTest::ParamType>& info) {
		return info.param.first;
	}
);
