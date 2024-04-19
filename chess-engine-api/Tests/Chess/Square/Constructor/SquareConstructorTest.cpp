#include "SquareConstructorTest.hpp"

SquareConstructorTest::SquareConstructorTest() : param(GetParam().second) {}

TEST_P(SquareConstructorTest, constructor) {
	Square square(param.position, param.piece);

	Position actualPosition = square.getPosition();
	std::shared_ptr<Piece> actualPiece = square.getPiece();

	Position expectedPosition = param.position;
	std::shared_ptr<Piece> expectedPiece = param.piece;

	ASSERT_EQ(actualPosition, expectedPosition);
	ASSERT_EQ(actualPiece, expectedPiece);
}

std::vector<std::pair<std::string, SquareConstructorTestParam>> SquareConstructorTest::testCases = {
	{"PawnAtOrigin", {{0, 0}, std::make_shared<Pawn>(Pawn(Color::White, {0, 0}))}},
	{"RookAtOrigin", {{0, 0}, std::make_shared<Rook>(Rook(Color::White, {0, 0}))}},
	{"KnightAtOrigin", {{0, 0}, std::make_shared<Knight>(Knight(Color::White, {0, 0}))}},
	{"BishopAtOrigin", {{0, 0}, std::make_shared<Bishop>(Bishop(Color::White, {0, 0}))}},
	{"QueenAtOrigin", {{0, 0}, std::make_shared<Queen>(Queen(Color::White, {0, 0}))}},
	{"KingAtOrigin", {{0, 0}, std::make_shared<King>(King(Color::White, {0, 0}))}},
	{"NullAtOrigin", {{0, 0}, nullptr}},
	{"PawnAtMax", {{7, 7}, std::make_shared<Pawn>(Pawn(Color::Black, {7, 7}))}},
	{"RookAtMax", {{7, 7}, std::make_shared<Rook>(Rook(Color::Black, {7, 7}))}},
	{"KnightAtMax", {{7, 7}, std::make_shared<Knight>(Knight(Color::Black, {7, 7}))}},
	{"BishopAtMax", {{7, 7}, std::make_shared<Bishop>(Bishop(Color::Black, {7, 7}))}},
	{"QueenAtMax", {{7, 7}, std::make_shared<Queen>(Queen(Color::Black, {7, 7}))}},
	{"KingAtMax", {{7, 7}, std::make_shared<King>(King(Color::Black, {7, 7}))}},
	{"NullAtMax", {{7, 7}, nullptr}},
	{"PawnAtMiddle", {{3, 3}, std::make_shared<Pawn>(Pawn(Color::White, {3, 3}))}},
	{"RookAtMiddle", {{3, 3}, std::make_shared<Rook>(Rook(Color::White, {3, 3}))}},
	{"KnightAtMiddle", {{3, 3}, std::make_shared<Knight>(Knight(Color::White, {3, 3}))}},
	{"BishopAtMiddle", {{4, 4}, std::make_shared<Bishop>(Bishop(Color::Black, {4, 4}))}},
	{"QueenAtMiddle", {{3, 3}, std::make_shared<Queen>(Queen(Color::Black, {4, 4}))}},
	{"KingAtMiddle", {{3, 3}, std::make_shared<King>(King(Color::Black, {4, 4}))}},
	{"NullAtMiddle", {{3, 3}, nullptr}}
};

INSTANTIATE_TEST_SUITE_P(
    SquareConstructor,
    SquareConstructorTest,
    ::testing::ValuesIn(SquareConstructorTest::testCases),
	[](const testing::TestParamInfo<SquareConstructorTest::ParamType>& info) {
		return info.param.first;
	}
);