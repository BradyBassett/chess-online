// #include "BitboardXORTest.hpp"

// BitboardXORTest::BitboardXORTest() : param(GetParam().second) {}

// TEST_P(BitboardXORTest, BitwiseXorEquals)
// {
// 	Bitboard initialBitboard = param.initialBitboard;
// 	Bitboard operationParameter = std::get<Bitboard>(param.operationParameter);
// 	Bitboard actualResult = initialBitboard ^= operationParameter;
// 	Bitboard expectedResult = param.expectedResult;

// 	ASSERT_EQ(actualResult, expectedResult);
// }

// std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardXORTest::testCases = {

// };

// INSTANTIATE_TEST_SUITE_P(
// 	BitboardXOR,
// 	BitboardXORTest,
// 	::testing::ValuesIn(BitboardXORTest::testCases),
// 	[](const testing::TestParamInfo<BitboardXORTest::ParamType> &info)
// 	{
// 		return info.param.first;
// 	});