#include "PawnCanPromoteTest.hpp"

PawnCanPromoteTest::PawnCanPromoteTest() : param(GetParam().second) {}

TEST_P(PawnCanPromoteTest, canPromote)
{
	Pawn pawn(param.color, param.currentPosition);

	bool result = pawn.canPromote(param.currentPosition);

	ASSERT_EQ(result, param.expectedResult);
}

std::vector<std::pair<std::string, PawnCanPromoteTestParam>> PawnCanPromoteTest::testCases = {
	{"CanPromote_WhitePawnOnLastRow", {Color::White, {0, 7}, true}},
	{"CanPromote_BlackPawnOnLastRow", {Color::Black, {7, 0}, true}},
	{"CanPromote_WhitePawnOnLastRow_DifferentColumn", {Color::White, {0, 0}, true}},
	{"CanPromote_BlackPawnOnLastRow_DifferentColumn", {Color::Black, {7, 7}, true}},
    {"CanPromote_WhitePawnOnLastRow_MiddleColumn", {Color::White, {0, 3}, true}},
    {"CanPromote_BlackPawnOnLastRow_MiddleColumn", {Color::Black, {7, 4}, true}},
	{"CannotPromote_WhitePawnNotOnLastRow", {Color::White, {3, 4}, false}},
	{"CannotPromote_BlackPawnNotOnLastRow", {Color::Black, {2, 5}, false}},
	{"CannotPromote_WhitePawnNotOnLastRow_DifferentColumn", {Color::White, {3, 7}, false}},
	{"CannotPromote_BlackPawnNotOnLastRow_DifferentColumn", {Color::Black, {2, 0}, false}},
	{"CannotPromote_WhitePawnOnFirstRow", {Color::White, {7, 0}, false}},
    {"CannotPromote_BlackPawnOnFirstRow", {Color::Black, {0, 7}, false}},
    {"CannotPromote_WhitePawnOnFirstRow_DifferentColumn", {Color::White, {7, 7}, false}},
    {"CannotPromote_BlackPawnOnFirstRow_DifferentColumn", {Color::Black, {0, 0}, false}},
    {"CannotPromote_WhitePawnNotOnLastRow_MiddleColumn", {Color::White, {3, 3}, false}},
    {"CannotPromote_BlackPawnNotOnLastRow_MiddleColumn", {Color::Black, {2, 4}, false}},
};

INSTANTIATE_TEST_SUITE_P(
	PawnCanPromote,
	PawnCanPromoteTest,
	::testing::ValuesIn(PawnCanPromoteTest::testCases),
	[](const testing::TestParamInfo<PawnCanPromoteTest::ParamType> &info) {
		return info.param.first;
	}
);