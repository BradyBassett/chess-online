#include "KingGenerateAttacksTest.hpp"

KingGenerateAttacksTest::KingGenerateAttacksTest() : param(GetParam().second) {}

TEST_P(KingGenerateAttacksTest, generateAttacks) {
    King king(param.color, param.currentPosition);
    Bitboard actualAttacks = king.generateAttacks();
    Bitboard expectedAttacks = Bitboard(param.expectedAttacks);

    ASSERT_EQ(actualAttacks, expectedAttacks);
}

std::vector<std::pair<std::string, PieceGenerateAttacksTestParam>> KingGenerateAttacksTest::testCases = {
    {"Center_Black", PieceGenerateAttacksTestParam{{3, 3}, Color::Black, 0x1c141c0000}},
    {"Center_White", PieceGenerateAttacksTestParam{{4, 4}, Color::White, 0x382838000000}},
    {"Corner_Black", PieceGenerateAttacksTestParam{{0, 0}, Color::Black, 0x302}},
    {"Corner_White", PieceGenerateAttacksTestParam{{7, 7}, Color::White, 0x40c0000000000000}},
    {"Edge_Black", PieceGenerateAttacksTestParam{{0, 3}, Color::White, 0x1c14}},
    {"Edge_White", PieceGenerateAttacksTestParam{{3, 0}, Color::White, 0x302030000}}
};

INSTANTIATE_TEST_SUITE_P(
    KingGenerateAttacks,
    KingGenerateAttacksTest,
    ::testing::ValuesIn(KingGenerateAttacksTest::testCases),
	[](const testing::TestParamInfo<KingGenerateAttacksTest::ParamType>& info) {
		return info.param.first;
	}
);
