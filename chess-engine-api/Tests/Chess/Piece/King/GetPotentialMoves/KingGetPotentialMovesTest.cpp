#include "KingGetPotentialMovesTest.hpp"

KingGetPotentialMovesTest::KingGetPotentialMovesTest() : param(GetParam().second) {}

TEST_P(KingGetPotentialMovesTest, getPotentialMoves) {
	King king(param.color, param.currentPosition);
	king.setHasMoved(param.hasMoved);
	king.setCanCastleKingside(param.canCastleKingside);
	king.setCanCastleQueenside(param.canCastleQueenside);

	Bitboard actualMoves = king.getPotentialMoves();
	Bitboard expectedMoves = Bitboard(param.expectedMoves);

	ASSERT_EQ(actualMoves, expectedMoves);
}

std::vector<std::pair<std::string, KingGetPotentialMovesTestParam>> KingGetPotentialMovesTest::testCases = {
	{"White_7_4_NotMoved_BothCastling_StartingPosition", {{7, 4}, Color::White, 0x6c38000000000000, false, true, true}},
	{"White_7_4_NotMoved_KingsideCastling_StartingPosition", {{7, 4}, Color::White, 0x6838000000000000, false, true, false}},
	{"White_7_4_NotMoved_QueensideCastling_StartingPosition", {{7, 4}, Color::White, 0x2c38000000000000, false, false, true}},
	{"White_7_4_NotMoved_NoCastling_StartingPosition", {{7, 4}, Color::White, 0x2838000000000000, false, false, false}},
	{"White_6_5_NotMoved_BothCastling_OtherPosition", {{6, 5}, Color::White, 0x7050700000000000, false, true, true}},
	{"White_0_5_NotMoved_KingsideCastling_OtherPosition", {{0, 5}, Color::White, 0x7050, false, true, false}},
	{"White_3_5_NotMoved_QueensideCastling_OtherPosition", {{3, 5}, Color::White, 0x7050700000, false, false, true}},
	{"White_7_0_NotMoved_NoCastling_OtherPosition", {{7, 0}, Color::White, 0x203000000000000, false, false, false}},
	{"White_7_4_Moved_BothCastling_StartingPosition", {{7, 4}, Color::White, 0x2838000000000000, true, true, true}},
	{"White_7_4_Moved_KingsideCastling_StartingPosition", {{7, 4}, Color::White, 0x2838000000000000, true, true, false}},
	{"White_7_4_Moved_QueensideCastling_StartingPosition", {{7, 4}, Color::White, 0x2838000000000000, true, false, true}},
	{"White_7_4_Moved_NoCastling_StartingPosition", {{7, 4}, Color::White, 0x2838000000000000, true, false, false}},
	{"White_4_1_Moved_BothCastling_OtherPosition", {{4, 1}, Color::White, 0x70507000000, true, true, true}},
	{"White_2_4_Moved_KingsideCastling_OtherPosition", {{2, 4}, Color::White, 0x38283800, true, true, false}},
	{"White_7_3_Moved_QueensideCastling_OtherPosition", {{7, 3}, Color::White, 0x141c000000000000, true, false, true}},
	{"White_0_0_Moved_NoCastling_OtherPosition", {{0, 0}, Color::White, 0x302, true, false, false}},
	{"Black_0_4_NotMoved_BothCastling_StartingPosition", {{0, 4}, Color::Black, 0x386c, false, true, true}},
	{"Black_0_4_NotMoved_KingsideCastling_StartingPosition", {{0, 4}, Color::Black, 0x3868, false, true, false}},
	{"Black_0_4_NotMoved_QueensideCastling_StartingPosition", {{0, 4}, Color::Black, 0x382c, false, false, true}},
	{"Black_0_4_NotMoved_NoCastling_StartingPosition", {{0, 4}, Color::Black, 0x3828, false, false, false}},
	{"Black_1_2_NotMoved_BothCastling_OtherPosition", {{1, 2}, Color::Black, 0xe0a0e, false, true, true}},
	{"Black_2_4_NotMoved_KingsideCastling_OtherPosition", {{2, 4}, Color::Black, 0x38283800, false, true, false}},
	{"Black_4_6_NotMoved_QueensideCastling_OtherPosition", {{4, 6}, Color::Black, 0xe0a0e0000000, false, false, true}},
	{"Black_0_7_NotMoved_NoCastling_OtherPosition", {{0, 7}, Color::Black, 0xc040, false, false, false}},
	{"Black_0_4_Moved_BothCastling_StartingPosition", {{0, 4}, Color::Black, 0x3828, true, true, true}},
	{"Black_0_4_Moved_KingsideCastling_StartingPosition", {{0, 4}, Color::Black, 0x3828, true, true, false}},
	{"Black_0_4_Moved_QueensideCastling_StartingPosition", {{0, 4}, Color::Black, 0x3828, true, false, true}},
	{"Black_0_4_Moved_NoCastling_StartingPosition", {{0, 4}, Color::Black, 0x3828, true, false, false}},
	{"Black_3_3_Moved_BothCastling_OtherPosition", {{3, 3}, Color::Black, 0x1c141c0000, true, true, true}},
	{"Black_6_6_Moved_KingsideCastling_OtherPosition", {{6, 6}, Color::Black, 0xe0a0e00000000000, true, true, false}},
	{"Black_4_3_Moved_QueensideCastling_OtherPosition", {{4, 3}, Color::Black, 0x1c141c000000, true, false, true}},
	{"Black_7_7_Moved_NoCastling_OtherPosition", {{7, 7}, Color::Black, 0x40c0000000000000, true, false, false}},
};

INSTANTIATE_TEST_SUITE_P(
	KingGetPotentialMoves,
	KingGetPotentialMovesTest,
	::testing::ValuesIn(KingGetPotentialMovesTest::testCases),
	[](const testing::TestParamInfo<KingGetPotentialMovesTest::ParamType>& info) {
		return info.param.first;
	}
);
