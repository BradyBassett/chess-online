#include "BitboardEqualityTest.hpp"

BitboardEqualityTest::BitboardEqualityTest() : param(GetParam().second) {}

TEST_P(BitboardEqualityTest, Equality)
{
	Bitboard initialBitboard = param.initialBitboard;
	Bitboard operationParameter = std::get<Bitboard>(param.operationParameter);
	Bitboard actualResult = initialBitboard == operationParameter;
	Bitboard expectedResult = param.expectedResult;

	ASSERT_EQ(actualResult, expectedResult);
}

std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardEqualityTest::testCases = {
    {"BothZero", {Bitboard(0x0), Bitboard(0x0), true}},
    {"ZeroAndNonZero", {Bitboard(0x0), Bitboard(0x1), false}},
    {"NonZeroAndZero", {Bitboard(0x1), Bitboard(0x0), false}},
    {"SameNonZero", {Bitboard(0x1), Bitboard(0x1), true}},
    {"DifferentNonZero", {Bitboard(0x1), Bitboard(0x2), false}},
    {"AllBitsSetAndZero", {Bitboard(0xffffffffffffffff), Bitboard(0x0), false}},
    {"AllBitsSetAndSame", {Bitboard(0xffffffffffffffff), Bitboard(0xffffffffffffffff), true}},
    {"RandomAndSame", generateRandomBitComparisonTestParam(ComparisonOperation::Equal)},
    {"RandomAndDifferent", generateRandomBitComparisonTestParam(ComparisonOperation::Equal, 0ULL, false)},
};

INSTANTIATE_TEST_SUITE_P(
	BitboardEquality,
	BitboardEqualityTest,
	::testing::ValuesIn(BitboardEqualityTest::testCases),
	[](const testing::TestParamInfo<BitboardEqualityTest::ParamType> &info)
	{
		return info.param.first;
	});