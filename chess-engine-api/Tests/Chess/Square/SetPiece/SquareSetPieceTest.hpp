#ifndef SQUARESETPIECETEST_HPP
#define SQUARESETPIECETEST_HPP

#include "../SquareTest.hpp"

class SquareSetPieceTest : public SquareTest, public testing::TestWithParam<std::pair<std::string, std::shared_ptr<Piece>>>
{
private:

protected:
	std::shared_ptr<Piece> param;

public:
	SquareSetPieceTest();
	static std::vector<std::pair<std::string, std::shared_ptr<Piece>>> testCases;
};

#endif // SQUARESETPIECETEST_HPP