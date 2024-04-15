#include "PawnGetPotentialMovesTest.hpp"

PawnGetPotentialMovesTest::PawnGetPotentialMovesTest() : param(GetParam().second) {}

TEST_P(PawnGetPotentialMovesTest, getPotentialMoves) {
	Pawn pawn(param.color, param.currentPosition);
	pawn.setHasMoved(param.hasMoved);

	Bitboard actualMoves = pawn.getPotentialMoves();
	Bitboard expectedMoves = Bitboard(param.expectedMoves);

	ASSERT_EQ(actualMoves, expectedMoves);
}

std::vector<std::pair<std::string, PawnGetPotentialMovesTestParam>> PawnGetPotentialMovesTest::testCases = {
	{"White_6_0_NotMoved_Starting_Start", {{6, 0}, Color::White, 0x30100000000, false}},
	{"White_6_4_NotMoved_Starting_Middle", {{6, 4}, Color::White, 0x381000000000, false}},
	{"White_6_7_NotMoved_Starting_End", {{6, 7}, Color::White, 0xc08000000000, false}},
	{"White_0_0_NotMoved_Other_Start", {{0, 0}, Color::White, 0x0, false}},
	{"White_7_4_NotMoved_Other_Middle", {{7, 4}, Color::White, 0x38000000000000, false}},
	{"White_5_7_NotMoved_Other_End", {{5, 7}, Color::White, 0xc000000000, false}},
	{"White_6_0_Moved_Starting_Start", {{6, 0}, Color::White, 0x30000000000, true}},
	{"White_6_4_Moved_Starting_Middle", {{6, 4}, Color::White, 0x380000000000, true}},
	{"White_6_7_Moved_Starting_End", {{6, 7}, Color::White, 0xc00000000000, true}},
	{"White_4_0_Moved_Other_Start", {{4, 0}, Color::White, 0x3000000, true}},
	{"White_4_4_Moved_Other_Middle", {{4, 4}, Color::White, 0x38000000, true}},
	{"White_3_7_Moved_Other_End", {{3, 7}, Color::White, 0xc00000, true}},
	{"Black_1_0_NotMoved_Starting_Start", {{1, 0}, Color::Black, 0x1030000, false}},
	{"Black_1_3_NotMoved_Starting_Middle", {{1, 3}, Color::Black, 0x81c0000, false}},
	{"Black_1_7_NotMoved_Starting_End", {{1, 7}, Color::Black, 0x80c00000, false}},
	{"Black_3_0_NotMoved_Other_Start", {{3, 0}, Color::Black, 0x300000000, false}},
	{"Black_2_3_NotMoved_Other_Middle", {{2, 3}, Color::Black, 0x1c000000, false}},
	{"Black_7_7_NotMoved_Other_End", {{7, 7}, Color::Black, 0x0, false}},
	{"Black_1_0_Moved_Starting_Start", {{1, 0}, Color::Black, 0x30000, true}},
	{"Black_1_3_Moved_Starting_Middle", {{1, 3}, Color::Black, 0x1c0000, true}},
	{"Black_1_7_Moved_Starting_End", {{1, 7}, Color::Black, 0xc00000, true}},
	{"Black_5_0_Moved_Other_Start", {{5, 0}, Color::Black, 0x3000000000000, true}},
	{"Black_0_3_Moved_Other_Middle", {{0, 3}, Color::Black, 0x1c00, true}},
	{"Black_5_7_Moved_Other_End", {{5, 7}, Color::Black, 0xc0000000000000, true}},
};

INSTANTIATE_TEST_SUITE_P(
	PawnGetPotentialMoves,
	PawnGetPotentialMovesTest,
	::testing::ValuesIn(PawnGetPotentialMovesTest::testCases),
	[](const testing::TestParamInfo<PawnGetPotentialMovesTest::ParamType>& info) {
		return info.param.first;
	}
);