#include "BitboardANDTest.hpp"

BitboardANDTest::BitboardANDTest() : param(GetParam().second) {}

TEST_P(BitboardANDTest, BitwiseAnd)
{
	Bitboard initialBitboard = param.initialBitboard;
	Bitboard operationParameter = std::get<Bitboard>(param.operationParameter);
	Bitboard actualResult = initialBitboard & operationParameter;
	Bitboard expectedResult = param.expectedResult;

	ASSERT_EQ(actualResult, expectedResult) << "Failed with initialBitboard value = " << initialBitboard.getValue()
											<< ", operationParameter value = " << operationParameter.getValue();
}

std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardANDTest::testCases = {
	{"AllBitsSet_AND_NoBitsSet", {Bitboard(0xffffffffffffffff), Bitboard(0x0), Bitboard(0x0)}},
	{"AllBitsSet_AND_AllBitsSet", {Bitboard(0xffffffffffffffff), Bitboard(0xffffffffffffffff), Bitboard(0xffffffffffffffff)}},
	{"AlternatingBits_AND_OppositeAlternatingBits", {Bitboard(0xaa55aa55aa55aa55), Bitboard(0x55aa55aa55aa55aa), Bitboard(0x0)}},
	{"AlternatingBits_AND_SameAlternatingBits", {Bitboard(0xaa55aa55aa55aa55), Bitboard(0xaa55aa55aa55aa55), Bitboard(0xaa55aa55aa55aa55)}},
	{"RandomBits_AND_RandomBits", generateRandomBitwiseTestParam(std::bit_and<uint64_t>{})},
	{"SingleBitSet_AND_NoBitsSet", {Bitboard(0x8000000), Bitboard(0x0), Bitboard(0x0)}},
	{"SingleBitSet_AND_SameSingleBitSet", {Bitboard(0x8000000), Bitboard(0x8000000), Bitboard(0x8000000)}},
	{"SingleBitSet_AND_DifferentSingleBitSet", {Bitboard(0x8000000), Bitboard(0x1000000000), Bitboard(0x0)}},
	{"SingleBitSet_AND_AllBitsSet", {Bitboard(0x20000000000000), Bitboard(0xffffffffffffffff), Bitboard(0x20000000000000)}},
	{"SingleBitSet_AND_RandomBits", generateRandomBitwiseTestParam(std::bit_and<uint64_t>{}, 0x20000000000000, false)},
};

INSTANTIATE_TEST_SUITE_P(
	BitboardAND,
	BitboardANDTest,
	::testing::ValuesIn(BitboardANDTest::testCases),
	[](const testing::TestParamInfo<BitboardANDTest::ParamType> &info)
	{
		return info.param.first;
	});