#ifndef BOARDISPATHCLEARTEST_HPP
#define BOARDISPATHCLEARTEST_HPP

#include "../BoardTest.hpp"
#include "../../../../Chess/models/Game.hpp"

struct BoardIsPathClearTestParam
{
	std::string fen;
	Position from;
	Position to;
	bool expected;
};

class BoardIsPathClearTest : public BoardTest, public ::testing::TestWithParam<std::pair<std::string, BoardIsPathClearTestParam>>
{
private:

protected:
	BoardIsPathClearTestParam param;

public:
	BoardIsPathClearTest();
	static std::vector<std::pair<std::string, BoardIsPathClearTestParam>> testCases;
};

#endif // BOARDISPATHCLEARTEST_HPP