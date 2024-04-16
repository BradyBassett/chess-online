#include "BitboardORTest.hpp"

BitboardORTest::BitboardORTest() : param(GetParam().second) {}

TEST_P(BitboardORTest, BitwiseOr)
{
	Bitboard initialBitboard = param.initialBitboard;
	Bitboard operationParameter = std::get<Bitboard>(param.operationParameter);
	Bitboard actualResult = initialBitboard | operationParameter;
	Bitboard expectedResult = param.expectedResult;

	ASSERT_EQ(actualResult, expectedResult);
}

std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardORTest::testCases = {
	{"Empty_bitboards", {Bitboard(0x0ULL), Bitboard(0x0ULL), Bitboard(0x0ULL)}},
	{"Empty_and_full_bitboards", {Bitboard(0x0ULL), Bitboard(~0x0ULL), Bitboard(~0x0ULL)}},
	{"Full_bitboards", {Bitboard(~0x0ULL), Bitboard(~0x0ULL), Bitboard(~0x0ULL)}},
	{"Single_bit_and_inverse", {Bitboard(0x1ULL), Bitboard(~0x1ULL), Bitboard(~0x0ULL)}},
};

INSTANTIATE_TEST_SUITE_P(
	BitboardOR,
	BitboardORTest,
	::testing::ValuesIn(BitboardORTest::testCases),
	[](const testing::TestParamInfo<BitboardORTest::ParamType> &info)
	{
		return info.param.first;
	});