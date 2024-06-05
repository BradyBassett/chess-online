#include "BoardIsPathClearTest.hpp"

BoardIsPathClearTest::BoardIsPathClearTest() : param(GetParam().second) {}

TEST_P(BoardIsPathClearTest, isPathClear) {
	Game game(param.fen);
	Board &board = game.getBoard();

	std::shared_ptr<Piece> piece = board.getSquare(param.from).getPiece();

	bool actual = board.isPathClear(param.from, param.to, piece);

	EXPECT_EQ(actual, param.expected);
}

std::vector<std::pair<std::string, BoardIsPathClearTestParam>> BoardIsPathClearTest::testCases = {
	{
		"Pawn_ClearPath_6_4_4_4",
		{
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
			{6, 4}, {4, 4}, true
		}
	},
	{
		"Pawn_ObstructedPath_6_4_4_4",
		{
			"rnbqkbnr/pppp1ppp/4p3/8/8/5N2/PPPPPPPP/RNBQKB1R w KQkq - 0 2",
			{6, 5}, {4, 5}, false
		}
	},
	{
		"Bishop_ClearPath_0_5_4_1",
		{
			"rnbqkbnr/pppp1ppp/4p3/8/8/1P3N2/P1PPPPPP/RNBQKB1R b KQkq - 0 2",
			{0, 5}, {4, 1}, true
		}
	},
	{
		"Bishop_ObstructedPath_7_5_5_7",
		{
			"rnbqk1nr/pppp1ppp/4p3/8/1b6/1P3N2/P1PPPPPP/RNBQKB1R w KQkq - 1 3",
			{7, 5}, {5, 7}, false
		}
	},
		{
		"Rook_ClearPath_7_0_2_0",
		{
			"r1bqk1nr/pppp1ppp/2n1p3/8/1b1N4/8/2PPPPPP/RNBQKB1R w KQkq - 0 6",
			{7, 0}, {2, 0}, true
		}
	},
	{
		"Rook_ObstructedPath_0_0_7_0",
		{
			"r1bqk1nr/1pp2ppp/R2p4/8/3Bp3/8/2P1PPPP/1N1QKB1R b Kkq - 1 11",
			{0, 0}, {7, 0}, false
		}
	},
	{
		"Rook_ObstructedPath_7_0_4_0",
		{
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
			{7, 0}, {4, 0}, false
		}
	},
	{
		"Rook_ObstructedPath_0_0_4_0",
		{
			"rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR b KQkq - 0 1",
			{0, 0}, {4, 0}, false
		}
	},
};

INSTANTIATE_TEST_SUITE_P(
	BoardIsPathClearTests,
	BoardIsPathClearTest,
	::testing::ValuesIn(BoardIsPathClearTest::testCases),
	[](const testing::TestParamInfo<BoardIsPathClearTest::ParamType>& info) {
		return info.param.first;
	}
);
