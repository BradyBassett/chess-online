#include "BitboardShiftLeftTest.hpp"

BitboardShiftLeftTest::BitboardShiftLeftTest() : param(GetParam().second) {}

TEST_P(BitboardShiftLeftTest, BitwiseShiftLeft)
{
	Bitboard initialBitboard = param.initialBitboard;
	uint64_t operationParameter = std::get<uint64_t>(param.operationParameter);
	Bitboard actualResult = initialBitboard << operationParameter;
	Bitboard expectedResult = param.expectedResult;

	ASSERT_EQ(actualResult, expectedResult);
}

std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardShiftLeftTest::testCases = {
	{"NoBitsSet_ShiftLeftBy1", {Bitboard(0x0), 1ULL, Bitboard(0x0)}},
	{"SingleBitSet_ShiftLeftBy1", {Bitboard(0x10000000), 1ULL, Bitboard(0x20000000)}},
	{"SingleBitSet_ShiftLeftBy63", {Bitboard(0x1), 63ULL, Bitboard(0x8000000000000000)}},
	{"AllBitsSet_ShiftLeftBy1", {Bitboard(0xffffffffffffffff), 1ULL, Bitboard(0xfffffffffffffffe)}},
	{"AllBitsSet_ShiftLeftBy64", {Bitboard(0xffffffffffffffff), 64ULL, Bitboard(0x0)}},
	{"AlternatingBits_ShiftLeftBy1", {Bitboard(0x5555555555555555), 1ULL, Bitboard(0xaaaaaaaaaaaaaaaa)}},
	{"AlternatingBits_ShiftLeftBy32", {Bitboard(0x5555555555555555), 32ULL, Bitboard(0x5555555500000000)}},
	{"RandomBits_ShiftLeftByRandom", generateRandomBitShiftTestParam(ShiftDirection::Left)},
	{"RandomBits_ShiftLeftBy1", generateRandomBitShiftTestParam(ShiftDirection::Left, 1ULL, false)},
	{"SingleBitSet_ShiftLeftBy0", {Bitboard(0x8000000000000000), 0ULL, Bitboard(0x8000000000000000)}},
	{"SingleBitSet_ShiftLeftBy64", {Bitboard(0x1), 64ULL, Bitboard(0x0)}},
};

INSTANTIATE_TEST_SUITE_P(
	BitboardShiftLeft,
	BitboardShiftLeftTest,
	::testing::ValuesIn(BitboardShiftLeftTest::testCases),
	[](const testing::TestParamInfo<BitboardShiftLeftTest::ParamType> &info)
	{
		return info.param.first;
	});