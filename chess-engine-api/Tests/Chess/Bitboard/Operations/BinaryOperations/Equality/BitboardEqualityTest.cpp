// #include "BitboardEqualityTest.hpp"

// BitboardEqualityTest::BitboardEqualityTest() : param(GetParam().second) {}

// TEST_P(BitboardEqualityTest, Equality)
// {
// 	Bitboard initialBitboard = param.initialBitboard;
// 	Bitboard operationParameter = std::get<Bitboard>(param.operationParameter);
// 	Bitboard actualResult = initialBitboard == operationParameter;
// 	Bitboard expectedResult = param.expectedResult;

// 	ASSERT_EQ(actualResult, expectedResult);
// }

// std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardEqualityTest::testCases = {

// };

// INSTANTIATE_TEST_SUITE_P(
// 	BitboardEquality,
// 	BitboardEqualityTest,
// 	::testing::ValuesIn(BitboardEqualityTest::testCases),
// 	[](const testing::TestParamInfo<BitboardEqualityTest::ParamType> &info)
// 	{
// 		return info.param.first;
// 	});