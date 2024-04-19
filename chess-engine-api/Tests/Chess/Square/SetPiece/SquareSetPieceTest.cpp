#include "SquareSetPieceTest.hpp"

SquareSetPieceTest::SquareSetPieceTest() : param(GetParam().second) {}

TEST_P(SquareSetPieceTest, setPiece) {
	Square square({0, 0});

	square.setPiece(param);

	std::shared_ptr<Piece> actualPiece = square.getPiece();
	std::shared_ptr<Piece> expectedPiece = param;

	ASSERT_EQ(actualPiece, expectedPiece);
}

std::vector<std::pair<std::string, std::shared_ptr<Piece>>> SquareSetPieceTest::testCases = {
	{"Pawn", std::make_shared<Pawn>(Pawn(Color::White, {0, 0}))},
	{"Rook", std::make_shared<Rook>(Rook(Color::White, {0, 0}))},
	{"Knight", std::make_shared<Knight>(Knight(Color::White, {0, 0}))},
	{"Bishop", std::make_shared<Bishop>(Bishop(Color::White, {0, 0}))},
	{"Queen", std::make_shared<Queen>(Queen(Color::White, {0, 0}))},
	{"King", std::make_shared<King>(King(Color::White, {0, 0}))},
	{"Null", nullptr}
};

INSTANTIATE_TEST_SUITE_P(
	SquareSetPiece,
	SquareSetPieceTest,
	::testing::ValuesIn(SquareSetPieceTest::testCases),
	[](const testing::TestParamInfo<SquareSetPieceTest::ParamType>& info) {
		return info.param.first;
	}
);