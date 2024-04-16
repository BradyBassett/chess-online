// #include "BitboardInequalityBitboardTest.hpp"

// BitboardInequalityBitboardTest::BitboardInequalityBitboardTest() : param(GetParam().second) {}

// TEST_P(BitboardInequalityBitboardTest, Inequality_Bitboard)
// {
// 	Bitboard initialBitboard = param.initialBitboard;
// 	Bitboard operationParameter = std::get<Bitboard>(param.operationParameter);
// 	Bitboard actualResult = initialBitboard != operationParameter;
// 	Bitboard expectedResult = param.expectedResult;

// 	ASSERT_EQ(actualResult, expectedResult);
// }

// std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardInequalityBitboardTest::testCases = {

// };

// INSTANTIATE_TEST_SUITE_P(
// 	BitboardInequalityBitboard,
// 	BitboardInequalityBitboardTest,
// 	::testing::ValuesIn(BitboardInequalityBitboardTest::testCases),
// 	[](const testing::TestParamInfo<BitboardInequalityBitboardTest::ParamType> &info)
// 	{
// 		return info.param.first;
// 	});