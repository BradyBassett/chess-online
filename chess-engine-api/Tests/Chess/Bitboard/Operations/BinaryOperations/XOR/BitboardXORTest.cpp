#include "BitboardXORTest.hpp"

BitboardXORTest::BitboardXORTest() : param(GetParam().second) {}

TEST_P(BitboardXORTest, BitwiseXorEquals)
{
	Bitboard initialBitboard = param.initialBitboard;
	Bitboard operationParameter = std::get<Bitboard>(param.operationParameter);
	Bitboard actualResult = initialBitboard ^= operationParameter;
	Bitboard expectedResult = param.expectedResult;

	ASSERT_EQ(actualResult, expectedResult);
}

std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardXORTest::testCases = {
	{"AllBitsSet_XOR_NoBitsSet", {Bitboard(0xffffffffffffffff), Bitboard(0x0), Bitboard(0xffffffffffffffff)}},
	{"AllBitsSet_XOR_AllBitsSet", {Bitboard(0xffffffffffffffff), Bitboard(0xffffffffffffffff), Bitboard(0x0)}},
	{"AlternatingBits_XOR_OppositeAlternatingBits", {Bitboard(0xaa55aa55aa55aa55), Bitboard(0x55aa55aa55aa55aa), Bitboard(0xffffffffffffffff)}},
	{"AlternatingBits_XOR_SameAlternatingBits", {Bitboard(0xaa55aa55aa55aa55), Bitboard(0xaa55aa55aa55aa55), Bitboard(0x0)}},
	{"RandomBits_XOR_RandomBits", generateRandomTestParam(std::bit_xor<uint64_t>{})},
	{"SingleBitSet_XOR_NoBitsSet", {Bitboard(0x800000), Bitboard(0x0), Bitboard(0x800000)}},
	{"SingleBitSet_XOR_SameSingleBitSet", {Bitboard(0x8000000), Bitboard(0x8000000), Bitboard(0x0)}},
	{"SingleBitSet_XOR_DifferentSingleBitSet", {Bitboard(0x800), Bitboard(0x80000000000), Bitboard(0x80000000800)}},
	{"SingleBitSet_XOR_AllBitsSet", {Bitboard(0x400000000), Bitboard(0xffffffffffffffff), Bitboard(0xfffffffbffffffff)}},
	{"SingleBitSet_XOR_RandomBits", generateRandomTestParam(std::bit_xor<uint64_t>{}, 0x20000000000000, false)},
};

INSTANTIATE_TEST_SUITE_P(
	BitboardXOR,
	BitboardXORTest,
	::testing::ValuesIn(BitboardXORTest::testCases),
	[](const testing::TestParamInfo<BitboardXORTest::ParamType> &info)
	{
		return info.param.first;
	});