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
	{"AllBitsSet_OR_NoBitsSet", {Bitboard(0xffffffffffffffff), Bitboard(0x0), Bitboard(0xffffffffffffffff)}},
	{"AllBitsSet_OR_AllBitsSet", {Bitboard(0xffffffffffffffff), Bitboard(0xffffffffffffffff), Bitboard(0xffffffffffffffff)}},
	{"AlternatingBits_OR_OppositeAlternatingBits", {Bitboard(0xaa55aa55aa55aa55), Bitboard(0x55aa55aa55aa55aa), Bitboard(0xffffffffffffffff)}},
	{"AlternatingBits_OR_SameAlternatingBits", {Bitboard(0xaa55aa55aa55aa55), Bitboard(0xaa55aa55aa55aa55), Bitboard(0xaa55aa55aa55aa55)}},
	{"RandomBits_OR_RandomBits", generateRandomTestParam(std::bit_or<uint64_t>{})},
	{"SingleBitSet_OR_NoBitsSet", {Bitboard(0x800000), Bitboard(0x0), Bitboard(0x800000)}},
	{"SingleBitSet_OR_SameSingleBitSet", {Bitboard(0x8000000), Bitboard(0x8000000), Bitboard(0x8000000)}},
	{"SingleBitSet_OR_DifferentSingleBitSet", {Bitboard(0x800), Bitboard(0x80000000000), Bitboard(0x80000000800)}},
	{"SingleBitSet_OR_AllBitsSet", {Bitboard(0x400000000), Bitboard(0xffffffffffffffff), Bitboard(0xffffffffffffffff)}},
	{"SingleBitSet_OR_RandomBits", generateRandomTestParam(std::bit_or<uint64_t>{}, 0x20000000000000, false)},
};

INSTANTIATE_TEST_SUITE_P(
	BitboardOR,
	BitboardORTest,
	::testing::ValuesIn(BitboardORTest::testCases),
	[](const testing::TestParamInfo<BitboardORTest::ParamType> &info)
	{
		return info.param.first;
	});