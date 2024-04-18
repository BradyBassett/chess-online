#include "BitboardNotTest.hpp"

BitboardNotTest::BitboardNotTest() : param(GetParam().second) {}

TEST_P(BitboardNotTest, NOT)
{
	Bitboard initialBitboard = param.initialBitboard;
	Bitboard actualResult = ~initialBitboard;
	Bitboard expectedResult = param.expectedResult;

	ASSERT_EQ(actualResult, expectedResult);
}

std::vector<std::pair<std::string, BitboardNotTestParam>> BitboardNotTest::testCases = {
    {"Zero", {Bitboard(0x0), Bitboard(0xffffffffffffffff)}},
    {"NonZero", {Bitboard(0x1), Bitboard(0xfffffffffffffffe)}},
    {"AllBitsSet", {Bitboard(0xffffffffffffffff), Bitboard(0x0)}},
    {"AlternatingBitsSet", {Bitboard(0x5555555555555555), Bitboard(0xaaaaaaaaaaaaaaaa)}},
    {"LeastSignificantBitSet", {Bitboard(0x1), Bitboard(0xfffffffffffffffe)}},
    {"MostSignificantBitSet", {Bitboard(0x8000000000000000), Bitboard(0x7fffffffffffffff)}},
    {"EveryOtherBitSetFromSecond", {Bitboard(0xaaaaaaaaaaaaaaaa), Bitboard(0x5555555555555555)}},
};

INSTANTIATE_TEST_SUITE_P(
	BitboardNot,
	BitboardNotTest,
	::testing::ValuesIn(BitboardNotTest::testCases),
	[](const testing::TestParamInfo<BitboardNotTest::ParamType> &info)
	{
		return info.param.first;
	});