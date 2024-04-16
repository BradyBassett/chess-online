// #include "BitboardShiftRightTest.hpp"

// BitboardShiftRightTest::BitboardShiftRightTest() : param(GetParam().second) {}

// TEST_P(BitboardShiftRightTest, BitwiseShiftRight)
// {
// 	Bitboard initialBitboard = param.initialBitboard;
// 	uint64_t operationParameter = std::get<uint64_t>(param.operationParameter);
// 	Bitboard actualResult = initialBitboard >> operationParameter;
// 	Bitboard expectedResult = param.expectedResult;

// 	ASSERT_EQ(actualResult, expectedResult);
// }

// std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardShiftRightTest::testCases = {

// };

// INSTANTIATE_TEST_SUITE_P(
// 	BitboardShiftRight,
// 	BitboardShiftRightTest,
// 	::testing::ValuesIn(BitboardShiftRightTest::testCases),
// 	[](const testing::TestParamInfo<BitboardShiftRightTest::ParamType> &info)
// 	{
// 		return info.param.first;
// 	});