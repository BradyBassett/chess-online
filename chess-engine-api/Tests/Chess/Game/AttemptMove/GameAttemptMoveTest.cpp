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
	{
		"InvalidKingMove_6_0_6_1",
		{
			"8/3P4/p1p3k1/2B4b/1N3P2/1r2R1n1/KP4Q1/3B2b1 w - - 0 1",
			{6, 0}, {6, 1}, '\0', false,
			""
		}
	},
	{
		"InvalidKingMove_2_3_2_5",
		{
			"8/4p1np/3k2pp/1P4b1/3P3R/n4p2/QP6/4K2N b - - 0 1",
			{2, 3}, {2, 5}, '\0', false,
			""
		}
	},
	{
		"InvalidKingMove_5_6_4_4",
		{
			"8/8/3PpPBr/1r3pp1/1PbN4/k1b3K1/2q1P3/8 w - - 0 1",
			{5, 6}, {4, 4}, '\0', false,
			""
		}
	},
	{
		"InvalidKingMove_7_4_7_6",
		{
			"rnbqkbnr/pp2p2p/8/3Pp3/2p2B2/5N2/PPPP2PR/RNBQK3 w Qkq - 0 1",
			{7, 4}, {7, 6}, '\0', false,
			""
		}
	},
	{
		"ValidCapture_Pawn_6_5_5_6",
		{
			"3n4/1P6/1pP4q/8/1R6/p1R3p1/k3PP1b/3K1B1r w - - 0 1",
			{6, 5}, {5, 6}, '\0', true,
			"3n4/1P6/1pP4q/8/1R6/p1R3P1/k3P2b/3K1B1r b - - 0 1"
		}
	},
	{
		"ValidCapture_Bishop_5_3_6_2",
		{
			"r7/1n3P2/3R4/1p3PP1/1P3K2/1p1Br2P/2n5/3N2k1 w - - 0 2",
			{5, 3}, {6, 2}, '\0', true,
			"r7/1n3P2/3R4/1p3PP1/1P3K2/1p2r2P/2B5/3N2k1 b - - 0 2"
		}
	},
	{
		"ValidCapture_Knight_5_5_4_3",
		{
			"8/pB1p4/1P2k3/2pb2pR/K2R4/2P2n2/2p3r1/8 b - - 3 4",
			{5, 5}, {4, 3}, '\0', true,
			"8/pB1p4/1P2k3/2pb2pR/K2n4/2P5/2p3r1/8 w - - 0 5"
		}
	},
	{
		"ValidCapture_Queen_7_5_0_5",
		{
			"5Q2/1pBP4/P7/2bP4/7P/3PN1K1/4p2p/1k1n1q2 b - - 0 1",
			{7, 5}, {0, 5}, '\0', true,
			"5q2/1pBP4/P7/2bP4/7P/3PN1K1/4p2p/1k1n4 w - - 0 2"
		}
	},
	{
		"ValidCapture_Rook_6_1_6_3",
		{
			"8/K2Ppk2/P1P5/2Q5/pPp3pp/1P6/1R1pP3/8 w - - 0 1",
			{6, 1}, {6, 3}, '\0', true,
			"8/K2Ppk2/P1P5/2Q5/pPp3pp/1P6/3RP3/8 b - - 0 1"
		}
	},
	{
		"ValidCapture_King_5_3_5_2",
		{
			"7Q/P3P3/3n1P2/4ppkN/1B6/2pK2P1/4B2p/4r3 w - - 0 1",
			{5, 3}, {5, 2}, '\0', true,
			"7Q/P3P3/3n1P2/4ppkN/1B6/2K3P1/4B2p/4r3 b - - 0 1"
		}
	},
	{
		"InvalidCapture_Pawn_4_3_3_3",
		{
			"5k2/4pn2/B6p/Rr1P4/2np1KP1/2b5/4PNN1/8 b - - 0 1",
			{4, 3}, {3, 3}, '\0', false,
			""
		}
	},
	{
		"InvalidCapture_Bishop_5_4_5_7",
		{
			"b7/R4K1p/5b2/P2P3p/1p6/3kBq1r/1Pp3P1/8 w - - 0 1",
			{5, 4}, {5, 7}, '\0', false,
			""
		}
	},
	{
		"InvalidCapture_Knight_0_3_1_4",
		{
			"3n2b1/4P3/1qP3KB/5p2/p2Rr3/1P3r2/2k1p2P/8 b - - 0 1",
			{0, 3}, {1, 4}, '\0', false,
			""
		}
	},
	{
		"InvalidCapture_Rook_7_1_6_2",
		{
			"1K5k/6r1/2B5/n3p1P1/8/P2pP1P1/2r1N2p/1Rb5 w - - 0 1",
			{7, 1}, {6, 2}, '\0', false,
			""
		}
	},
	{
		"InvalidCapture_Queen_4_1_4_7",
		{
			"1Q6/1N3p2/8/3P2pK/1qP4B/1P2p2b/5n2/1r1r2k1 w - - 0 1",
			{4, 1}, {4, 7}, '\0', false,
			""
		}
	},
	{
		"InvalidCapture_King_2_6_4_4",
		{
			"1qrR2K1/1Qn5/p1p3k1/6N1/4P3/pp6/2P5/2b1N3 b - - 0 1",
			{2, 6}, {4, 4}, '\0', false,
			""
		}
	},
	{
		"MovingIntoCheck_Pawn_4_2_3_1",
		{
			"2K3n1/4R3/8/1r4P1/2P5/Pp4N1/1p1B1kpP/2r2N1B w - - 0 1",
			{4, 2}, {3, 1}, '\0', false,
			""
		}
	},
	{
		"MovingIntoCheck_Bishop_1_2_2_1",
		{
			"2R3K1/2b2P2/2kp1p1P/1p3P2/4np1R/2r2p2/7q/7B b - - 0 1",
			{1, 2}, {2, 1}, '\0', false,
			""
		}
	},
	{
		"MovingIntoCheck_Knight_2_4_1_2",
		{
			"3PB2Q/8/pr2NK2/p2k1P2/P5b1/q3R3/4PR2/r7 w - - 0 1",
			{2, 4}, {1, 2}, '\0', false,
			""
		}
	},
	{
		"MovingIntoCheck_Rook_1_4_2_4",
		{
			"N2k4/2N1r3/P4B1p/2q3p1/b1p4P/8/2p5/K3n1n1 b - - 0 1",
			{1, 4}, {2, 4}, '\0', false,
			""
		}
	},
	{
		"MovingIntoCheck_Queen_1_6_2_6",
		{
			"1r3b2/1k1p2Q1/1P4nK/2pp1PPp/4P3/P4p2/6n1/8 w - - 0 1",
			{1, 6}, {2, 6}, '\0', false,
			""
		}
	},
	{
		"MovingIntoCheck_King_6_4_5_3",
		{
			"7N/p4p2/2PP4/1R1pKB2/5nPq/6P1/2Pbk3/8 b - - 0 1",
			{6, 4}, {5, 3}, '\0', false,
			""
		}
	},
	{
		"Valid_White_Kingside_Castle",
		{
			"r3k2r/p2p2pp/b1nbpp1n/1pp1P3/3qQPP1/2PBB2N/PP1NP2P/R3K2R w KQkq - 0 1",
			{7, 4}, {7, 6}, '\0', true,
			"r3k2r/p2p2pp/b1nbpp1n/1pp1P3/3qQPP1/2PBB2N/PP1NP2P/R4RK1 b kq - 1 1"
		}
	},
	{
		"Valid_White_Queenside_Castle",
		{
			"r3k2r/p2p2pp/b1nbpp1n/1pp1P3/3qQPP1/2PBB2N/PP1NP2P/R3K2R w KQkq - 0 1",
			{7, 4}, {7, 2}, '\0', true,
			"r3k2r/p2p2pp/b1nbpp1n/1pp1P3/3qQPP1/2PBB2N/PP1NP2P/2KR3R b kq - 1 1"
		}
	},
	{
		"Valid_Black_Kingside_Castle",
		{
			"r3k2r/p2p2pp/b1nbpp1n/1pp1P3/3qQPP1/2PBB2N/PP1NP2P/R3K2R b KQkq - 0 1",
			{0, 4}, {0, 6}, '\0', true,
			"r4rk1/p2p2pp/b1nbpp1n/1pp1P3/3qQPP1/2PBB2N/PP1NP2P/R3K2R w KQ - 1 2"
		}
	},
	{
		"Valid_Black_Queenside_Castle",
		{
			"r3k2r/p2p2pp/b1nbpp1n/1pp1P3/3qQPP1/2PBB2N/PP1NP2P/R3K2R b KQkq - 0 1",
			{0, 4}, {0, 2}, '\0', true,
			""
		}
	},
};

// Castling: Test both kingside and queenside castling, as well as situations where castling is not allowed (e.g., if the king has already moved, if there is a piece between the king and the rook, or if the king would pass through or land in check).

// Pawn promotion: Test that a pawn can be promoted to a queen, rook, bishop, or knight when it reaches the opponent's back rank.

// En passant: Test the special pawn capturing move of en passant.


INSTANTIATE_TEST_SUITE_P(
	GameAttemptMove,
	GameAttemptMoveTest,
	::testing::ValuesIn(GameAttemptMoveTest::testCases),
	[](const testing::TestParamInfo<GameAttemptMoveTest::ParamType>& info) {
		return info.param.first;
	}
);