#include "BitboardInequalityBitboardTest.hpp"

BitboardInequalityBitboardTest::BitboardInequalityBitboardTest() : param(GetParam().second) {}

TEST_P(BitboardInequalityBitboardTest, Inequality_Bitboard)
{
	Bitboard initialBitboard = param.initialBitboard;
	Bitboard operationParameter = std::get<Bitboard>(param.operationParameter);
	Bitboard actualResult = initialBitboard != operationParameter;
	Bitboard expectedResult = param.expectedResult;

	ASSERT_EQ(actualResult, expectedResult);
}

std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardInequalityBitboardTest::testCases = {
    {"BothZero", {Bitboard(0x0), Bitboard(0x0), false}},
    {"ZeroAndNonZero", {Bitboard(0x0), Bitboard(0x1), true}},
    {"NonZeroAndZero", {Bitboard(0x1), Bitboard(0x0), true}},
    {"SameNonZero", {Bitboard(0x1), Bitboard(0x1), false}},
    {"DifferentNonZero", {Bitboard(0x1), Bitboard(0x2), true}},
    {"AllBitsSetAndZero", {Bitboard(0xffffffffffffffff), Bitboard(0x0), true}},
    {"AllBitsSetAndSame", {Bitboard(0xffffffffffffffff), Bitboard(0xffffffffffffffff), false}},
    {"RandomAndSame", generateRandomBitComparisonTestParam(ComparisonOperation::NotEqual)},
    {"RandomAndDifferent", generateRandomBitComparisonTestParam(ComparisonOperation::NotEqual, 0ULL, false)},
};

INSTANTIATE_TEST_SUITE_P(
	BitboardInequalityBitboard,
	BitboardInequalityBitboardTest,
	::testing::ValuesIn(BitboardInequalityBitboardTest::testCases),
	[](const testing::TestParamInfo<BitboardInequalityBitboardTest::ParamType> &info)
	{
		return info.param.first;
	});