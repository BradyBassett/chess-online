#include "PawnCanMoveOneSquareTest.hpp"

PawnCanMoveOneSquareTest::PawnCanMoveOneSquareTest() : param(GetParam().second) {}

TEST_P(PawnCanMoveOneSquareTest, canMoveOneSquare) {
	Pawn pawn(param.color, param.currentPosition);

	bool result = pawn.canMoveOneSquare(param.targetPosition);

	ASSERT_EQ(result, param.expectedResult);
}

std::vector<std::pair<std::string, PawnCanMoveOneSquareTestParam>> PawnCanMoveOneSquareTest::testCases = {
	{"White_2_3_1_3_ValidMove", {Color::White, {2, 3}, {1, 3}, true}},
	{"Black_2_3_3_3_ValidMove", {Color::Black, {2, 3}, {3, 3}, true}},
	{"White_2_3_0_3_InvalidMove", {Color::White, {2, 3}, {0, 3}, false}},
	{"Black_2_3_4_3_InvalidMove", {Color::Black, {2, 3}, {4, 3}, false}},
	{"White_6_0_5_0_ValidMove", {Color::White, {6, 0}, {5, 0}, true}},
	{"Black_1_7_2_7_ValidMove", {Color::Black, {1, 7}, {2, 7}, true}},
	{"White_6_3_5_3_ValidMove", {Color::White, {6, 3}, {5, 3}, true}},
	{"Black_1_4_2_4_ValidMove", {Color::Black, {1, 4}, {2, 4}, true}},
	{"White_2_3_0_3_Invalid_LongForward", {Color::White, {2, 3}, {0, 3}, false}},
	{"Black_2_3_4_3_Invalid_LongForward", {Color::Black, {2, 3}, {4, 3}, false}},
	{"White_2_3_2_4_Invalid_Sideways", {Color::White, {2, 3}, {2, 4}, false}},
	{"Black_2_3_2_2_Invalid_Sideways", {Color::Black, {2, 3}, {2, 2}, false}},
	{"White_2_3_1_4_Invalid_Diagonal", {Color::White, {2, 3}, {1, 4}, false}},
	{"Black_2_3_3_2_Invalid_Diagonal", {Color::Black, {2, 3}, {3, 2}, false}},
	{"White_2_3_3_3_Invalid_Backwards", {Color::White, {2, 3}, {3, 3}, false}},
	{"Black_2_3_1_3_Invalid_Backwards", {Color::Black, {2, 3}, {1, 3}, false}},
};

INSTANTIATE_TEST_SUITE_P(
	PawnCanMoveOneSquare,
	PawnCanMoveOneSquareTest,
	::testing::ValuesIn(PawnCanMoveOneSquareTest::testCases),
	[](const testing::TestParamInfo<PawnCanMoveOneSquareTest::ParamType>& info) {
		return info.param.first;
	}
);