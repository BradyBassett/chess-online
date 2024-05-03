#include "GameAttemptMoveTest.hpp"

GameAttemptMoveTest::GameAttemptMoveTest() : param(GetParam().second) {}

TEST_P(GameAttemptMoveTest, attemptMove) {
	Game game(param.fen);

	if (param.isValid)
	{
		EXPECT_NO_THROW(game.attemptMove(param.from, param.to, param.promotion));
		std::string actualFen = game.getFen();
		EXPECT_EQ(actualFen, param.expectedFen);
	}
	else
	{
		EXPECT_THROW(game.attemptMove(param.from, param.to, param.promotion), std::invalid_argument);
	}
}

std::vector<std::pair<std::string, GameAttemptMoveTestParam>> GameAttemptMoveTest::testCases = {
	{
		"ValidPawnMove_6_4_5_4",
		{
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
			{6, 4}, {5, 4}, '\0', true,
			"rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1"
		}
	},
	{
		"ValidPawnMove_1_4_3_4",
		{
			"rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1",
			{1, 4}, {3, 4}, '\0', true,
			"rnbqkbnr/pppp1ppp/8/4p3/8/4P3/PPPP1PPP/RNBQKBNR w KQkq e6 0 2"
		}
	},
	{
		"InvalidPawnMove_6_2_4_2",
		{
			"rnbqkbnr/ppp1pppp/3p4/8/8/2N5/PPPPPPPP/R1BQKBNR w KQkq - 0 2",
			{6, 2}, {4, 2}, '\0', false,
			""
		}
	},
	{
		"InvalidPawnMove_7_0_6_1",
		{
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
			{7, 0}, {6, 1}, '\0', false,
			""
		}
	},
	{
		"InvalidPawnMove_2_3_3_3",
		{
			"rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR b KQkq - 0 1",
			{1, 3}, {4, 3}, '\0', false,
			""
		}
	},
	{
		"ValidBishopMove_7_5_4_2",
		{
			"rnbqkbnr/pppp1ppp/4p3/8/8/4P3/PPPP1PPP/RNBQKBNR w KQkq - 0 2",
			{7, 5}, {4, 2}, '\0', true,
			"rnbqkbnr/pppp1ppp/4p3/8/2B5/4P3/PPPP1PPP/RNBQK1NR b KQkq - 1 2"
		}
	},
	{
		"ValidBishopMove_0_5_1_4",
		{
			"rnbqkbnr/pppp1ppp/4p3/8/2B5/4P3/PPPP1PPP/RNBQK1NR b KQkq - 1 2",
			{0, 5}, {1, 4}, '\0', true,
			"rnbqk1nr/ppppbppp/4p3/8/2B5/4P3/PPPP1PPP/RNBQK1NR w KQkq - 2 3"
		}
	},
	{
		"InvalidBishopMove_7_2_6_3",
		{
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
			{7, 2}, {6, 3}, '\0', false,
			""
		}
	},
	{
		"InvalidBishopMove_2_3_4_3",
		{
			"rnbqk1nr/pppp1ppp/3b4/4p3/4P3/3P1P2/PPP3PP/RNBQKBNR b KQkq - 0 3",
			{2, 3}, {4, 3}, '\0', false,
			""
		}
	},
	{
		"InvalidBishopMove_2_1_1_0",
		{
			"2b5/p2NBp1p/1bp1nPPr/3P4/2pRnr1P/1k1B1Ppp/1P1P1pQP/Rq1N3K b - - 0 1",
			{2, 1}, {1, 0}, '\0', false,
			""
		}
	},
	{
		"InvalidBishopMove_1_2_6_6",
		{
			"8/1QBN2k1/8/1pp2b1K/6r1/2RP2q1/1p2P1p1/5n2 w - - 0 1",
			{1, 2}, {6, 6}, '\0', false,
			""
		}
	},
	{
		"ValidKnightMove_7_6_5_5",
		{
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
			{7, 6}, {5, 5}, '\0', true,
			"rnbqkbnr/pppppppp/8/8/8/5N2/PPPPPPPP/RNBQKB1R b KQkq - 1 1"
		}
	},
	{
		"ValidKnightMove_2_5_1_3",
		{
			"rnbqkb1r/pp3ppp/5n2/1Bp1p3/3P4/2N1PN2/PP3PPP/R1BQK2R b KQkq - 1 7",
			{2, 5}, {1, 3}, '\0', true,
			"rnbqkb1r/pp1n1ppp/8/1Bp1p3/3P4/2N1PN2/PP3PPP/R1BQK2R w KQkq - 2 8"
		}
	},
	{
		"ValidKnightMove_5_5_3_4",
		{
			"rnbqkb1r/pp1n1ppp/8/1Bp1p3/3P4/2N1PN2/PP3PPP/R1BQK2R w KQkq - 2 8",
			{5, 5}, {3, 4}, '\0', true,
			"rnbqkb1r/pp1n1ppp/8/1Bp1N3/3P4/2N1P3/PP3PPP/R1BQK2R b KQkq - 0 8"
		}
	},
	{
		"InvalidKnightMove_6_0_5_1",
		{
			"8/1P2p2R/1p3k2/N1r5/3bKP1R/1p6/NP5n/6B1 w - - 0 1",
			{6, 0}, {5, 1}, '\0', false,
			""
		}
	},
	{
		"InvalidKnightMove_6_1_1_6",
		{
			"r7/N3P3/6KP/1pk1p2P/1p5p/8/1n3nPq/6R1 b - - 0 1",
			{6, 1}, {1, 6}, '\0', false,
			""
		}
	},
	{
		"InvalidKnightMove_7_0_0_7",
		{
			"8/1PKb1p1N/4p1p1/R7/5Pk1/3p4/3npb2/n3R3 w - - 0 1",
			{7, 0}, {0, 7}, '\0', false,
			""
		}
	},
	{
		"InvalidKnightMove_5_0_6_2",
		{
			"6q1/6p1/8/R5Pp/1P1P1p2/nBRP3K/2p5/2k2n2 b - - 0 1",
			{5, 0}, {6, 2}, '\0', false,
			""
		}
	},
	{
		"ValidRookMove_7_0_2_0",
		{
			"rnbqkbnr/p1p1pppp/3p4/1P6/8/8/1PPPPPPP/RNBQKBNR w KQkq - 0 3",
			{7, 0}, {2, 0}, '\0', true,
			"rnbqkbnr/p1p1pppp/R2p4/1P6/8/8/1PPPPPPP/1NBQKBNR b Kkq - 1 3"
		}
	},
	{
		"ValidRookMove_0_0_0_3",
		{
			"r3kbnr/pbpqpppp/n2p4/1P6/3P4/2N2P2/1PP1P1PP/2BQKBNR b Kkq - 0 6",
			{0, 0}, {0, 3}, '\0', true,
			"3rkbnr/pbpqpppp/n2p4/1P6/3P4/2N2P2/1PP1P1PP/2BQKBNR w Kk - 1 7"
		}
	},
	{
		"InvalidRookMove_7_0_4_0",
		{
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
			{7, 0}, {4, 0}, '\0', false,
			""
		}
	},
	{
		"InvalidRookMove_0_0_0_5",
		{
			"r2qk1nr/ppp1bppp/2npp3/5b2/3P3P/4PPP1/PPP5/RNBQKBNR b KQkq - 0 6",
			{0, 0}, {0, 5}, '\0', false,
			""
		}
	},
	{
		"InvalidRookMove_7_7_3_3",
		{
			"r2qk1nr/ppp1bppp/2np2b1/4p3/3P1P1P/4P1P1/PPP5/RNBQKBNR w KQkq - 0 8",
			{7, 7}, {3, 3}, '\0', false,
			""
		}
	},
	{
		"InvalidRookMove_0_0_2_1",
		{
			"r2qk1nr/ppp1bppp/2np2b1/4p3/3P1P1P/4P1PR/PPP5/RNBQKBN1 b Qkq - 1 8",
			{0, 0}, {2, 1}, '\0', false,
			""
		}
	},
	{
		"ValidQueenMove_3_2_0_2",
		{
			"1b2n2r/3P1pp1/P5p1/2q1k3/8/3P4/p2P4/1N1K4 b - - 1 2",
			{3, 2}, {0, 2}, '\0', true,
			"1bq1n2r/3P1pp1/P5p1/4k3/8/3P4/p2P4/1N1K4 w - - 2 3"
		}
	},
	{
		"ValidQueenMove_7_0_7_7",
		{
			"B7/k5nN/6p1/6Kb/P1Pp1r1R/8/P4qP1/Q7 w - - 0 1",
			{7, 0}, {7, 7}, '\0', true,
			"B7/k5nN/6p1/6Kb/P1Pp1r1R/8/P4qP1/7Q b - - 1 1"
		}
	},
	{
		"ValidQueenMove_7_0_5_2",
		{
			"B7/k5nN/6p1/6Kb/P1Pp1r1R/8/P4qP1/Q7 w - - 0 1",
			{7, 0}, {5, 2}, '\0', true,
			"B7/k5nN/6p1/6Kb/P1Pp1r1R/2Q5/P4qP1/8 b - - 1 1"
		}
	},
	{
		"InvalidQueenMove_6_5_6_7",
		{
			"B7/k5nN/6p1/6Kb/P1Pp1r1R/2Q5/P4qP1/8 b - - 1 1",
			{6, 5}, {6, 7}, '\0', false,
			""
		}
	},
	{
		"InvalidQueenMove_5_2_0_2",
		{
			"B7/k5nN/6p1/6Kb/P1Pp1r1R/2Q5/P4qP1/8 b - - 1 1",
			{5, 2}, {0, 2}, '\0', false,
			""
		}
	},
	{
		"InvalidQueenMove_7_7_6_5",
		{
			"1R6/3p3n/2p5/K5B1/1p1p1P2/Npqk4/6pb/7Q w - - 0 1",
			{7, 7}, {6, 5}, '\0', false,
			""
		}
	},
	{
		"InvalidQueenMove_5_2_5_0",
		{
			"B7/k5nN/6p1/6Kb/P1Pp1r1R/2Q5/P4qP1/8 b - - 1 1",
			{5, 2}, {5, 0}, '\0', false,
			""
		}
	},
	{
		"ValidKingMove_7_4_6_4",
		{
			"rnbqkbnr/pppp1ppp/4p3/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2",
			{7, 4}, {6, 4}, '\0', true,
			"rnbqkbnr/pppp1ppp/4p3/8/4P3/8/PPPPKPPP/RNBQ1BNR b kq - 1 2"
		}
	},
	{
		"ValidKingMove_0_4_1_3",
		{
			"rnbqkbnr/ppp1pppp/3p4/8/3P4/4P3/PPP2PPP/RNBQKBNR b KQkq d3 0 2",
			{0, 4}, {1, 3}, '\0', true,
			"rnbq1bnr/pppkpppp/3p4/8/3P4/4P3/PPP2PPP/RNBQKBNR w KQ - 1 3"
		}
	},
};

// Valid moves for each piece type: Test that each type of piece (pawn, rook, knight, bishop, queen, king) can make a valid move.

// Invalid moves for each piece type: Test that each type of piece cannot make a move that is not allowed by the rules of chess.

// Capture moves: Test that a piece can capture an opponent's piece.

// Invalid capture moves: Test that a piece cannot capture a piece if it's not allowed by the rules of chess.

// Moves that result in check: Test that a move that would put the player's own king in check is not allowed.

// Moves that get out of check: Test that a player in check must make a move that gets their king out of check.

// Castling: Test both kingside and queenside castling, as well as situations where castling is not allowed (e.g., if the king has already moved, if there is a piece between the king and the rook, or if the king would pass through or land in check).

// Pawn promotion: Test that a pawn can be promoted to a queen, rook, bishop, or knight when it reaches the opponent's back rank.

// En passant: Test the special pawn capturing move of en passant.

// Checkmate and stalemate situations: Test that the game recognizes checkmate and stalemate situations correctly.


INSTANTIATE_TEST_SUITE_P(
	GameAttemptMove,
	GameAttemptMoveTest,
	::testing::ValuesIn(GameAttemptMoveTest::testCases),
	[](const testing::TestParamInfo<GameAttemptMoveTest::ParamType>& info) {
		return info.param.first;
	}
);