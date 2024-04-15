#include "PawnCanMoveOneOrTwoSquaresTest.hpp"

PawnCanMoveOneOrTwoSquaresTest::PawnCanMoveOneOrTwoSquaresTest() : param(GetParam().second) {}

TEST_P(PawnCanMoveOneOrTwoSquaresTest, canMoveTwoSquares)
{
	Pawn pawn(param.color, param.currentPosition);

	bool result = pawn.canMoveOneOrTwoSquares(param.targetPosition);
	pawn.setHasMoved(param.hasMoved);

	ASSERT_EQ(result, param.expectedResult);
}

std::vector<std::pair<std::string, PawnCanMoveOneOrTwoSquaresTestParam>> PawnCanMoveOneOrTwoSquaresTest::testCases = {
	{"White_6_3_4_3_Forwards_NotMoved_Valid", {Color::White, {6, 3}, {4, 3}, false, true}},
	{"Black_1_3_3_3_Forwards_NotMoved_Valid", {Color::Black, {1, 3}, {3, 3}, false, true}},
	{"White_6_0_4_0_Forwards_NotMoved_Valid", {Color::White, {6, 0}, {5, 0}, false, true}},
	{"Black_1_0_3_0_Forwards_NotMoved_Valid", {Color::Black, {1, 0}, {2, 0}, false, true}},
	{"White_6_7_4_7_Forwards_NotMoved_Valid", {Color::White, {6, 7}, {4, 7}, false, true}},
	{"Black_1_7_3_7_Forwards_NotMoved_Valid", {Color::Black, {1, 7}, {3, 7}, false, true}},
	{"White_6_4_4_4_Forwards_NotMoved_Valid", {Color::White, {6, 4}, {5, 4}, false, true}},
	{"Black_1_4_3_4_Forwards_NotMoved_Valid", {Color::Black, {1, 4}, {2, 4}, false, true}},
	{"White_5_3_4_3_Forwards_Moved_Valid", {Color::White, {5, 3}, {4, 3}, true, true}},
	{"Black_2_3_3_3_Forwards_Moved_Valid", {Color::Black, {2, 3}, {3, 3}, true, true}},
	{"White_5_0_4_0_Forwards_Moved_Valid", {Color::White, {5, 0}, {4, 0}, true, true}},
	{"Black_2_0_3_0_Forwards_Moved_Valid", {Color::Black, {2, 0}, {3, 0}, true, true}},
	{"White_6_3_7_3_Backwards_NotMoved_Invalid", {Color::White, {6, 3}, {7, 3}, false, false}},
	{"Black_1_3_0_3_Backwards_NotMoved_Invalid", {Color::Black, {1, 3}, {0, 3}, false, false}},
	{"White_6_3_5_3_Backwards_Moved_Invalid", {Color::White, {6, 3}, {7, 3}, true, false}},
	{"Black_1_3_2_3_Backwards_Moved_Invalid", {Color::Black, {1, 3}, {0, 3}, true, false}},
	{"White_6_3_5_4_Diagonal_NotMoved_Invalid", {Color::White, {6, 3}, {5, 4}, false, false}},
	{"Black_1_3_2_4_Diagonal_NotMoved_Invalid", {Color::Black, {1, 3}, {2, 4}, false, false}},
	{"White_6_3_5_4_Diagonal_Moved_Invalid", {Color::White, {6, 3}, {5, 4}, true, false}},
	{"Black_1_3_2_4_Diagonal_Moved_Invalid", {Color::Black, {1, 3}, {2, 4}, true, false}},
	{"White_6_3_4_4_Diagonal_Moved_Invalid", {Color::White, {6, 3}, {4, 4}, true, false}},
	{"Black_1_3_3_4_Diagonal_Moved_Invalid", {Color::Black, {1, 3}, {3, 4}, true, false}},
};

INSTANTIATE_TEST_SUITE_P(
	PawnCanMoveOneOrTwoSquares,
	PawnCanMoveOneOrTwoSquaresTest,
	::testing::ValuesIn(PawnCanMoveOneOrTwoSquaresTest::testCases),
	[](const testing::TestParamInfo<PawnCanMoveOneOrTwoSquaresTest::ParamType> &info)
	{
		return info.param.first;
	});
