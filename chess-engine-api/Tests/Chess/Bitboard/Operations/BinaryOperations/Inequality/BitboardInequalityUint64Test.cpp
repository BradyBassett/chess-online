// #include "BitboardInequalityUint64Test.hpp"

// BitboardInequalityUint64Test::BitboardInequalityUint64Test() : param(GetParam().second) {}

// TEST_P(BitboardInequalityUint64Test, Inequality_Uint64)
// {
// 	Bitboard initialBitboard = param.initialBitboard;
// 	uint64_t operationParameter = std::get<uint64_t>(param.operationParameter);
// 	Bitboard actualResult = initialBitboard != operationParameter;
// 	Bitboard expectedResult = param.expectedResult;

// 	ASSERT_EQ(actualResult, expectedResult);
// }

// std::vector<std::pair<std::string, BitboardBinaryOperationsTestParam>> BitboardInequalityUint64Test::testCases = {

// };

// INSTANTIATE_TEST_SUITE_P(
// 	BitboardInequalityUint64,
// 	BitboardInequalityUint64Test,
// 	::testing::ValuesIn(BitboardInequalityUint64Test::testCases),
// 	[](const testing::TestParamInfo<BitboardInequalityUint64Test::ParamType> &info)
// 	{
// 		return info.param.first;
// 	});