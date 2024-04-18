#include "BitboardShiftRightTest.hpp"

BitboardShiftRightTest::BitboardShiftRightTest() : param(GetParam().second) {}

TEST_P(BitboardShiftRightTest, BitwiseShiftRight)
{
	Bitboard initialBitboard = param.initialBitboard;
	uint64_t operationParameter = std::get<uint64_t>(param.operationParameter);
	Bitboard actualResult = initialBitboard >> operationParameter;
	Bitboard expectedResult = param.expectedResult;

	ASSERT_EQ(actualResult, expectedResult);
}

std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardShiftRightTest::testCases = {
    {"NoBitsSet_ShiftRightBy1", {Bitboard(0x0), 1ULL, Bitboard(0x0)}},
    {"SingleBitSet_ShiftRightBy1", {Bitboard(0x20000000), 1ULL, Bitboard(0x10000000)}},
    {"SingleBitSet_ShiftRightBy63", {Bitboard(0x8000000000000000), 63ULL, Bitboard(0x1)}},
    {"AllBitsSet_ShiftRightBy1", {Bitboard(0xffffffffffffffff), 1ULL, Bitboard(0x7fffffffffffffff)}},
    {"AllBitsSet_ShiftRightBy64", {Bitboard(0xffffffffffffffff), 64ULL, Bitboard(0x0)}},
    {"AlternatingBits_ShiftRightBy1", {Bitboard(0xaaaaaaaaaaaaaaaa), 1ULL, Bitboard(0x5555555555555555)}},
    {"AlternatingBits_ShiftRightBy32", {Bitboard(0x5555555500000000), 32ULL, Bitboard(0x55555555)}},
    {"RandomBits_ShiftRightByRandom", generateRandomBitShiftTestParam(ShiftDirection::Right)},
    {"RandomBits_ShiftRightBy1", generateRandomBitShiftTestParam(ShiftDirection::Right, 1ULL, false)},
    {"SingleBitSet_ShiftRightBy0", {Bitboard(0x8000000000000000), 0ULL, Bitboard(0x8000000000000000)}},
    {"SingleBitSet_ShiftRightBy64", {Bitboard(0x8000000000000000), 64ULL, Bitboard(0x0)}},
};

INSTANTIATE_TEST_SUITE_P(
	BitboardShiftRight,
	BitboardShiftRightTest,
	::testing::ValuesIn(BitboardShiftRightTest::testCases),
	[](const testing::TestParamInfo<BitboardShiftRightTest::ParamType> &info)
	{
		return info.param.first;
	});