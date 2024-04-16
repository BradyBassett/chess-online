// #include "BitboardShiftLeftTest.hpp"

// BitboardShiftLeftTest::BitboardShiftLeftTest() : param(GetParam().second) {}

// TEST_P(BitboardShiftLeftTest, BitwiseShiftLeft)
// {
// 	Bitboard initialBitboard = param.initialBitboard;
// 	uint64_t operationParameter = std::get<uint64_t>(param.operationParameter);
// 	Bitboard actualResult = initialBitboard << operationParameter;
// 	Bitboard expectedResult = param.expectedResult;

// 	ASSERT_EQ(actualResult, expectedResult);
// }

// std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardShiftLeftTest::testCases = {

// };

// INSTANTIATE_TEST_SUITE_P(
// 	BitboardShiftLeft,
// 	BitboardShiftLeftTest,
// 	::testing::ValuesIn(BitboardShiftLeftTest::testCases),
// 	[](const testing::TestParamInfo<BitboardShiftLeftTest::ParamType> &info)
// 	{
// 		return info.param.first;
// 	});