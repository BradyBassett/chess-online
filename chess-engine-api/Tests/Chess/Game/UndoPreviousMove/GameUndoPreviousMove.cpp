#include "GameUndoPreviousMove.hpp"

GameUndoPreviousMove::GameUndoPreviousMove() : param(GetParam().second) {};

TEST(GameUndoPreviousMove, NoPreviousMove)
{
	Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	ASSERT_THROW(game.undoPreviousMove(), std::invalid_argument);
}

TEST(GameUndoPreviousMove, MultipleMovesToUndo)
{
	Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	game.attemptMove({6, 4}, {5, 4}, '\0');

	ASSERT_EQ(game.getFen(), "rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1");

	game.attemptMove({1, 4}, {2, 4}, '\0');

	ASSERT_EQ(game.getFen(), "rnbqkbnr/pppp1ppp/4p3/8/8/4P3/PPPP1PPP/RNBQKBNR w KQkq - 0 2");

	game.attemptMove({7, 5}, {4, 2}, '\0');

	ASSERT_EQ(game.getFen(), "rnbqkbnr/pppp1ppp/4p3/8/2B5/4P3/PPPP1PPP/RNBQK1NR b KQkq - 1 2");

	game.attemptMove({1, 3}, {3, 3}, '\0');

	ASSERT_EQ(game.getFen(), "rnbqkbnr/ppp2ppp/4p3/3p4/2B5/4P3/PPPP1PPP/RNBQK1NR w KQkq d6 0 3");

	game.undoPreviousMove();

	ASSERT_EQ(game.getFen(), "rnbqkbnr/pppp1ppp/4p3/8/2B5/4P3/PPPP1PPP/RNBQK1NR b KQkq - 1 2");

	game.undoPreviousMove();

	ASSERT_EQ(game.getFen(), "rnbqkbnr/pppp1ppp/4p3/8/8/4P3/PPPP1PPP/RNBQKBNR w KQkq - 1 2");

	game.undoPreviousMove();

	ASSERT_EQ(game.getFen(), "rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1");

	game.undoPreviousMove();

	ASSERT_EQ(game.getFen(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

TEST_P(GameUndoPreviousMove, UndoPreviousMove)
{
	Game game(param.startingFen);

	for (std::tuple<Position, Position, char> move : param.moves)
	{
		game.attemptMove(std::get<0>(move), std::get<1>(move), std::get<2>(move));
	}

	game.undoPreviousMove();

	std::string actualFen = game.getFen();
	std::string expectedFen = param.expectedFen;

	ASSERT_EQ(actualFen, expectedFen) << "Actual: " << actualFen << " Expected: " << expectedFen;
}

std::vector<std::pair<std::string, GameUndoPreviousMoveParams>> GameUndoPreviousMove::testCases = {
	{
		"StandardWhitePawnMove",
		{
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
			{
				{{6, 4}, {5, 4}, '\0',}
			},
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
		}
	},
	{
		"StandardBlackPawnMove",
		{
			"rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1",
			{
				{{1, 4}, {2, 4}, '\0'}
			},
			"rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1",
		}
	},
	{
		"WhiteStandardCapture",
		{
			"rnbqkbnr/pp1p1ppp/2p5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 3",
			{
				{{5, 5}, {3, 4}, '\0'}
			},
			"rnbqkbnr/pp1p1ppp/2p5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 3"
		}
	},
	{
		"BlackStandardCapture",
		{
			"rnbqkb1r/pppp1ppp/5n2/4p3/4P3/1P5P/P1PP1PP1/RNBQKBNR b KQkq - 0 3",
			{
				{{2, 5}, {4, 4}, '\0'}
			},
			"rnbqkb1r/pppp1ppp/5n2/4p3/4P3/1P5P/P1PP1PP1/RNBQKBNR b KQkq - 0 3"
		}
	},
	{
		"WhitePawnPromotion",
		{
			"rnb3nr/ppppPp1p/2k3p1/8/1b5q/5N2/PPPP1PPP/RNBQKB1R w KQ - 0 8",
			{
				{{1, 4}, {0, 4}, 'q'}
			},
			"rnb3nr/ppppPp1p/2k3p1/8/1b5q/5N2/PPPP1PPP/RNBQKB1R w KQ - 0 8"
		}
	},
	{
		"BlackPawnPromotion",
		{
			"rnbq1b1r/ppp1kppp/4pn2/1B5Q/8/2K2P1N/PPPPp1PP/RNB4R b - - 1 8",
			{
				{{6, 4}, {7, 4}, 'n'}
			},
			"rnbq1b1r/ppp1kppp/4pn2/1B5Q/8/2K2P1N/PPPPp1PP/RNB4R b - - 1 8"
		}
	},
	{
		"WhitePawnPromotionWithCapture",
		{
			"1nbqkbnr/P2p2p1/1pprpp1p/8/8/2BP4/1PP1PPPP/RN1QKBNR w KQk - 0 9",
			{
				{{1, 0}, {0, 1}, 'r'}
			},
			"1nbqkbnr/P2p2p1/1pprpp1p/8/8/2BP4/1PP1PPPP/RN1QKBNR w KQk - 0 9"
		}
	},
	{
		"BlackPawnPromotionWithCapture",
		{
			"rn1qkbnr/1pp1pppp/3P4/1b6/3Q4/4P3/pP1P1PPP/RNB1KBNR b KQkq - 1 9",
			{
				{{6, 0}, {7, 1}, 'b'}
			},
			"rn1qkbnr/1pp1pppp/3P4/1b6/3Q4/4P3/pP1P1PPP/RNB1KBNR b KQkq - 1 9"
		}
	},
	// {
	// 	"WhiteEnPassantCapture",
	// 	{
	// 		"rnbqkbnr/p1ppp1pp/1p6/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3",
	// 		{
	// 			{{3, 4}, {2, 5}, '\0'}
	// 		},
	// 		"rnbqkbnr/p1ppp1pp/1p6/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3"
	// 	}
	// },
	// {
	// 	"BlackEnPassantCapture",
	// 	{
	// 		"",
	// 		{
	// 			{{0, 0}, {0, 0}, '\0'}
	// 		},
	// 		""
	// 	}
	// },
	// {
	// 	"WhiteKingsideCastling",
	// 	{
	// 		"rnbqkbnr/pppp2pp/5p2/4p3/8/4PN2/PPPPBPPP/RNBQK2R w KQkq - 0 4",
	// 		{
	// 			{{7, 4}, {7, 6}, '\0'}
	// 		},
	// 		"rnbqkbnr/pppp2pp/5p2/4p3/8/4PN2/PPPPBPPP/RNBQK2R w KQkq - 0 4"
	// 	}
	// },
	// {
	// 	"WhiteQueensideCastling",
	// 	{
	// 		"",
	// 		{
	// 			{{0, 0}, {0, 0}, '\0'}
	// 		},
	// 		""
	// 	}
	// },
	// {
	// 	"BlackKingsideCastling",
	// 	{
	// 		"",
	// 		{
	// 			{{0, 0}, {0, 0}, '\0'}
	// 		},
	// 		""
	// 	}
	// },
	// {
	// 	"BlackQueensideCastling",
	// 	{
	// 		"",
	// 		{
	// 			{{0, 0}, {0, 0}, '\0'}
	// 		},
	// 		""
	// 	}
	// },
	// {
	// 	"WhitePutsBlackInCheck",
	// 	{
	// 		"",
	// 		{
	// 			{{0, 0}, {0, 0}, '\0'}
	// 		},
	// 		""
	// 	}
	// },
	// {
	// 	"BlackPutsWhiteInCheck",
	// 	{
	// 		"",
	// 		{
	// 			{{0, 0}, {0, 0}, '\0'}
	// 		},
	// 		""
	// 	}
	// },

	// FIXME - These tests are failing for some reason
	{
		"WhiteDoublePawnPush",
		{
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
			{
				{{6, 4}, {4, 4}, '\0'}
			},
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
		}
	},
	{
		"BlackDoublePawnPush",
		{
			"rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1",
			{
				{{1, 4}, {3, 4}, '\0'}
			},
			"rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1"
		}
	},
};

INSTANTIATE_TEST_SUITE_P(
	GameUndoPreviousMove,
	GameUndoPreviousMove,
	::testing::ValuesIn(GameUndoPreviousMove::testCases),
	[](const testing::TestParamInfo<GameUndoPreviousMove::ParamType>& info) {
		return info.param.first;
	}
);