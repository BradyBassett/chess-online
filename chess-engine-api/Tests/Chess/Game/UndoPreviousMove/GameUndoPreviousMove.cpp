#include "GameUndoPreviousMove.hpp"

// scenario where the last move does not exist

// scenario where the last move was a pawn promotion

// scenario where the last move was a promotion with capture

// scenario where the last move was a standard capture move

// scenario where the last move was an en passant capture move

// scenario where the last move was a kingside castling move

// scenario where the last move was a queenside castling move

// scenario where the last move was a double pawn push move

// scenario where the last move was a standard black pawn move

// scenario where the last move was a standard white pawn move

// scenario where the last move put the opponent in check

// scenario where there are multiple moves to undo


GameUndoPreviousMove::GameUndoPreviousMove() : param(GetParam().second) {};

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
				{{6, 4}, {5, 4}, '\0'},
			},
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
		}
	},
	{
		"StandardBlackPawnMove",
		{
			"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
			{
				{{6, 4}, {5, 4}, '\0'},
				{{1, 4}, {2, 4}, '\0'}
			},
			"rnbqkbnr/pppppppp/8/8/8/4P3/PPPP1PPP/RNBQKBNR b KQkq - 0 1",
		}
	}
};

INSTANTIATE_TEST_SUITE_P(
	GameUndoPreviousMove,
	GameUndoPreviousMove,
	::testing::ValuesIn(GameUndoPreviousMove::testCases),
	[](const testing::TestParamInfo<GameUndoPreviousMove::ParamType>& info) {
		return info.param.first;
	}
);