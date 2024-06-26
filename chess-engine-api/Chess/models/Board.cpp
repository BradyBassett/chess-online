#include "Board.hpp"
#include <stdexcept>
#include <map>
#include <regex>
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"
#include "Pawn.hpp"

bool Board::isDigitFrom1To8(char c)
{
	std::string s(1, c);
	std::regex pattern("^[1-8]$");

	return std::regex_match(s, pattern);
}

std::vector<Square> Board::parseFenPosition(std::string &fenPosition)
{
	std::vector<Square> squares;

	uint8_t rowIndex = 0;
	uint8_t colIndex = 0;

	std::map<char, std::function<std::shared_ptr<Piece>(Square)>> pieceTypes = {
		{'r', [this](Square square)
		 {
			 std::shared_ptr<Rook> rook = std::make_shared<Rook>(Color::Black, square.getPosition(), getRookSide(square));
			 rooks.push_back(rook);
			 return rook;
		 }},
		{'n', [](Square square)
		 {
			 return std::make_shared<Knight>(Color::Black, square.getPosition());
		 }},
		{'b', [](Square square)
		 {
			 return std::make_shared<Bishop>(Color::Black, square.getPosition());
		 }},
		{'q', [](Square square)
		 {
			 return std::make_shared<Queen>(Color::Black, square.getPosition());
		 }},
		{'k', [this](Square square)
		 {
			 std::shared_ptr<King> king = std::make_shared<King>(Color::Black, square.getPosition());
			 kings.push_back(king);
			 return king;
		 }},
		{'p', [](Square square)
		 {
			 return std::make_shared<Pawn>(Color::Black, square.getPosition());
		 }},
		{'R', [this](Square square)
		 {
			 std::shared_ptr<Rook> rook = std::make_shared<Rook>(Color::White, square.getPosition(), getRookSide(square));
			 rooks.push_back(rook);
			 return rook;
		 }},
		{'N', [](Square square)
		 {
			 return std::make_shared<Knight>(Color::White, square.getPosition());
		 }},
		{'B', [](Square square)
		 {
			 return std::make_shared<Bishop>(Color::White, square.getPosition());
		 }},
		{'Q', [](Square square)
		 {
			 return std::make_shared<Queen>(Color::White, square.getPosition());
		 }},
		{'K', [this](Square square)
		 {
			 std::shared_ptr<King> king = std::make_shared<King>(Color::White, square.getPosition());
			 kings.push_back(king);
			 return king;
		 }},
		{'P', [](Square square)
		 {
			 return std::make_shared<Pawn>(Color::White, square.getPosition());
		 }}};

	for (char c : fenPosition)
	{
		// If character is a /, start the next row, ensuring numSquaresPerRow is equal to 8
		if (c == '/')
		{
			if (colIndex != 8 || rowIndex >= 7)
			{
				throw std::invalid_argument("Invalid Fen Position");
			}
			colIndex = 0;
			rowIndex++;
		}
		// if the character is any digit from 1-8 add empty squares to pieces (represented as null)
		else if (isDigitFrom1To8(c))
		{
			for (int i = 0; i < c - '0'; i++)
			{
				squares.push_back(Square({rowIndex, colIndex}));
				colIndex++;
			}
		}
		// If the character is not "/", a digit from 1-8, or a key in pieceMappings throw an error
		else if (pieceTypes.count(c) == 0)
		{
			throw std::invalid_argument("Invalid Fen Position");
		}
		// All remaining possible characters should represent pieces
		else
		{
			Square square = Square({rowIndex, colIndex});
			std::shared_ptr<Piece> piece = pieceTypes[c](square);
			Bitboard &pieceBitboard = getBitboard(piece->getPieceColor(), piece->getPieceType());
			incrementPieceCount(piece->getPieceColor(), piece->getPieceType());
			pieceBitboard.setBit(square.getPosition());
			square.setPiece(piece);
			squares.push_back(square);
			colIndex++;
		}
	}

	return squares;
}

void Board::parseCastlingAvailability(const std::string &castling)
{
	setCanCastleKingside(castling.find('K') != std::string::npos, Color::White);
	setCanCastleQueenside(castling.find('Q') != std::string::npos, Color::White);
	setCanCastleKingside(castling.find('k') != std::string::npos, Color::Black);
	setCanCastleQueenside(castling.find('q') != std::string::npos, Color::Black);

	std::shared_ptr<King> whiteKing = getKing(Color::White);
	std::shared_ptr<King> blackKing = getKing(Color::Black);

	whiteKing->setCanCastleKingside(getCanCastleKingside(Color::White));
	whiteKing->setCanCastleQueenside(getCanCastleQueenside(Color::White));
	blackKing->setCanCastleKingside(getCanCastleKingside(Color::Black));
	blackKing->setCanCastleQueenside(getCanCastleQueenside(Color::Black));
}

void Board::parseEnPassantTarget(const std::string &enPassant)
{
	if (enPassant == "-")
	{
		setEnPassantTargetSquare(nullptr);
	}
	else
	{
		Position pos = convertStringToPosition(enPassant);
		setEnPassantTargetSquare(&getSquare(pos));
	}
}

void Board::movePiece(Square &fromSquare, Square &toSquare, std::shared_ptr<Piece> piece)
{
	Bitboard &pieceBitboard = getBitboard(piece->getPieceColor(), piece->getPieceType());
	pieceBitboard.clearBit(fromSquare.getPosition());
	pieceBitboard.setBit(toSquare.getPosition());

	if (toSquare.getPiece() != nullptr)
	{
		Bitboard &capturedPieceBitboard = getBitboard(toSquare.getPiece()->getPieceColor(), toSquare.getPiece()->getPieceType());
		capturedPieceBitboard.clearBit(toSquare.getPosition());
	}

	toSquare.setPiece(piece);
	fromSquare.setPiece(nullptr);
	piece->setHasMoved();
	piece->setCurrentPosition(toSquare.getPosition());
}

void Board::initializeStartingPosition(std::string fenPosition)
{
	squares.clear();

	std::vector<Square> parsedSquares = parseFenPosition(fenPosition);

	for (int i = 0; i < parsedSquares.size(); i += 8)
	{
		squares.push_back(std::vector<Square>(parsedSquares.begin() + i, parsedSquares.begin() + i + 8));
	}
}

void Board::initializeBitboards()
{
	// initialize bitboards to 0
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			bitboards[i][j].setValue(0ULL);
		}
	}
}

void Board::initializeAttackTables()
{
	Pawn whitePawn = Pawn(Color::White, Position{0, 0});
	Pawn blackPawn = Pawn(Color::Black, Position{0, 0});
	Knight knight = Knight(Color::White, Position{0, 0});
	Bishop bishop = Bishop(Color::White, Position{0, 0});
	Rook rook = Rook(Color::White, Position{0, 0});
	Queen queen = Queen(Color::White, Position{0, 0});
	King king = King(Color::White, Position{0, 0});

	for (uint8_t i = 0; i < 64; i++)
	{
		Position pos = Position{i / 8, i % 8};

		whitePawn.setCurrentPosition(pos);
		blackPawn.setCurrentPosition(pos);
		knight.setCurrentPosition(pos);
		bishop.setCurrentPosition(pos);
		rook.setCurrentPosition(pos);
		queen.setCurrentPosition(pos);
		king.setCurrentPosition(pos);

		pawnAttackTable[0][i] = whitePawn.generateAttacks();
		pawnAttackTable[1][i] = blackPawn.generateAttacks();
		knightAttackTable[i] = knight.generateAttacks();
		bishopAttackTable[i] = bishop.generateAttacks();
		rookAttackTable[i] = rook.generateAttacks();
		queenAttackTable[i] = queen.generateAttacks();
		kingAttackTable[i] = king.generateAttacks();
	}
}

bool Board::isPathClear(Position from, Position to, std::shared_ptr<Piece> piece)
{
	Bitboard path = calculatePath(from, to, piece);
	Bitboard allPieces = getAllPiecesBitboard();

	Bitboard x = path & allPieces;

	return (path & allPieces) == 0;
}

Bitboard Board::calculatePath(Position from, Position to, std::shared_ptr<Piece> piece)
{
	// Use the piece's move generation to calculate the path, excluding the target square because it can contain a piece to be captured
	Bitboard path;
	switch (piece->getPieceType())
	{
	case PieceType::Pawn:
	{
		if (piece->getHasMoved())
		{
			break;
		}

		int direction = (piece->getPieceColor() == Color::White) ? -1 : 1;
		if (from.row + (direction * 2) == to.row && from.col == to.col)
		{
			path.setBit({from.row + direction, from.col});
		}
		break;
	}
	case PieceType::Bishop:
	{
		if (!isDiagonal(from, to))
		{
			throw std::invalid_argument("Invalid move - Bishops can only move diagonally");
		}

		path = calculateDiagonalPath(from, to);
		break;
	}
	case PieceType::Rook:
	{
		if (!isOrthagonal(from, to))
		{
			throw std::invalid_argument("Invalid move - Rooks can only move orthagonally");
		}

		path = calculateOrthagonalPath(from, to);
		break;
	}
	case PieceType::Queen:
	{
		if (isDiagonal(from, to))
		{
			path = calculateDiagonalPath(from, to);
		}
		else if (isOrthagonal(from, to))
		{
			path = calculateOrthagonalPath(from, to);
		}
		else
		{
			throw std::invalid_argument("Invalid move - Queens can only move orthagonally or diagonally");
		}
		break;
	}
	}

	return path;
}

Bitboard Board::calculateDiagonalPath(Position from, Position to)
{
	Bitboard path;
	int rowStep = (to.row - from.row) > 0 ? 1 : -1;
	int colStep = (to.col - from.col) > 0 ? 1 : -1;

	uint8_t i = from.row + rowStep;
	uint8_t j = from.col + colStep;

	while ((rowStep > 0 ? i < to.row : i > to.row) &&
		   (colStep > 0 ? j < to.col : j > to.col))
	{
		path.setBit({i, j});
		i += rowStep;
		j += colStep;
	}

	return path;
}

bool Board::isDiagonal(Position from, Position to) const
{
	return abs(to.row - from.row) == abs(to.col - from.col);
}

Bitboard Board::calculateOrthagonalPath(Position from, Position to)
{
	Bitboard path;
	if (to.row == from.row)
	{
		uint8_t colStart = std::min(to.col, from.col);
		uint8_t colEnd = std::max(to.col, from.col);

		for (int i = colStart + 1; i < colEnd; i++)
		{
			path.setBit({from.row, i});
		}
	}
	else if (to.col == from.col)
	{
		uint8_t rowStart = std::min(to.row, from.row);
		uint8_t rowEnd = std::max(to.row, from.row);

		for (int i = rowStart + 1; i < rowEnd; i++)
		{
			path.setBit({i, from.col});
		}
	}

	return path;
}

bool Board::isOrthagonal(Position from, Position to) const
{
	return to.row == from.row || to.col == from.col;
}

bool Board::isCastleMove(Position from, Position to) const
{
	if (from.col == 4 && (to.col == 6 || to.col == 2))
	{
		return true;
	}

	return false;
}

Board::Board() : Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", "KQkq", "-") {}

Board::Board(std::string fenPosition, std::string castlingAvailability, std::string enPassantTarget)
{
	initializeBitboards();
	initializeStartingPosition(fenPosition);
	parseCastlingAvailability(castlingAvailability);
	parseEnPassantTarget(enPassantTarget);
	initializeAttackTables();
}

Square &Board::getSquare(int rowIndex, int colIndex)
{
	uint8_t boardSize = squares.size();
	if (rowIndex < 0 || rowIndex >= boardSize || colIndex < 0 || colIndex >= boardSize)
	{
		throw std::out_of_range("Square coordinates are out of range");
	}
	return squares[rowIndex][colIndex];
}

Square &Board::getSquare(Position position)
{
	uint8_t boardSize = squares.size();
	if (position.row < 0 || position.row >= boardSize || position.col < 0 || position.col >= boardSize)
	{
		throw std::out_of_range("Square coordinates are out of range");
	}
	return squares[position.row][position.col];
}

Square &Board::getSquare(int squareNumber)
{
	uint8_t boardSize = squares.size();
	if (squareNumber < 0 || squareNumber >= boardSize * boardSize)
	{
		throw std::out_of_range("Square number is out of range");
	}
	return squares[squareNumber / boardSize][squareNumber % boardSize];
}

std::vector<std::vector<Square>> Board::getSquares()
{
	return squares;
}

void Board::setupMove(Move move)
{
	Square &fromSquare = getSquare(move.from);
	Square &toSquare = getSquare(move.to);
	std::shared_ptr<Piece> piece = fromSquare.getPiece();

	// If the move is a castling move, move the rook as well
	if (piece->getPieceType() == PieceType::King && !piece->getHasMoved() && isCastleMove(move.from, move.to))
	{
		if (move.flags.test(static_cast<int>(MoveFlag::KingsideCastling)))
		{
			std::shared_ptr<Rook> rook = getRook(piece->getPieceColor(), Side::KingSide);
			Square &rookFromSquare = getSquare(move.from.row, 7);
			Square &rookToSquare = getSquare(move.to.row, 5);
			movePiece(rookFromSquare, rookToSquare, rook);
		}
		else if (move.flags.test(static_cast<int>(MoveFlag::QueensideCastling)))
		{
			std::shared_ptr<Rook> rook = getRook(piece->getPieceColor(), Side::QueenSide);
			Square &rookFromSquare = getSquare(move.from.row, 0);
			Square &rookToSquare = getSquare(move.to.row, 3);
			movePiece(rookFromSquare, rookToSquare, rook);
		}
	}

	// If the move is an en passant move, remove the captured pawn
	if (move.flags.test(static_cast<int>(MoveFlag::EnPassant)))
	{
		// remove from board and bitboard
		Square &capturedPawnSquare = getSquare(move.from.row, move.to.col);
		capturedPawnSquare.setPiece(nullptr);
		Bitboard &capturedPawnBitboard = getBitboard(piece->getPieceColor() == Color::White ? Color::Black : Color::White, PieceType::Pawn);
		capturedPawnBitboard.clearBit(capturedPawnSquare.getPosition());
	}

	movePiece(fromSquare, toSquare, piece);
}

std::shared_ptr<Rook> Board::getRook(Color color, Side side)
{
	for (std::shared_ptr<Rook> rook : rooks)
	{
		if (rook->getPieceColor() == color && rook->getSide() == side)
		{
			return rook;
		}
	}

	throw std::invalid_argument("No rook found");
}

std::vector<std::shared_ptr<Rook>> Board::getRooks()
{
	return rooks;
}

std::shared_ptr<King> Board::getKing(Color color)
{
	for (std::shared_ptr<King> king : kings)
	{
		if (king->getPieceColor() == color)
		{
			return king;
		}
	}

	throw std::invalid_argument("No king found");
}

std::vector<std::shared_ptr<King>> Board::getKings()
{
	return kings;
}

Side Board::getRookSide(Square square)
{
	return (square.getPosition().col == 0) ? Side::QueenSide : Side::KingSide;
}

bool Board::getCanCastleKingside(Color color)
{
	return canCastleKingside[static_cast<int>(color)];
}

bool Board::getCanCastleQueenside(Color color)
{
	return canCastleQueenside[static_cast<int>(color)];
}

void Board::setCanCastleKingside(bool value, Color color)
{
	canCastleKingside[static_cast<int>(color)] = value;
}

void Board::setCanCastleQueenside(bool value, Color color)
{
	canCastleQueenside[static_cast<int>(color)] = value;
}

Bitboard &Board::getBitboard(Color color, PieceType pieceType)
{
	return bitboards[static_cast<int>(color)][static_cast<int>(pieceType)];
}

Bitboard Board::getWhitePiecesBitboard()
{
	return bitboards[0][0] | bitboards[0][1] | bitboards[0][2] | bitboards[0][3] | bitboards[0][4] | bitboards[0][5];
}

Bitboard Board::getBlackPiecesBitboard()
{
	return bitboards[1][0] | bitboards[1][1] | bitboards[1][2] | bitboards[1][3] | bitboards[1][4] | bitboards[1][5];
}

Bitboard Board::getAllPiecesBitboard()
{
	return getWhitePiecesBitboard() | getBlackPiecesBitboard();
}

void Board::updateCastlingAvailability(Piece &fromPiece)
{
	if (fromPiece.getHasMoved())
	{
		PieceType pieceType = fromPiece.getPieceType();
		Color color = fromPiece.getPieceColor();

		if (pieceType == PieceType::King)
		{
			King king = dynamic_cast<King &>(fromPiece);
			setCanCastleKingside(false, color);
			setCanCastleQueenside(false, color);
			king.setCanCastleKingside(false);
			king.setCanCastleQueenside(false);
		}
		else if (pieceType == PieceType::Rook)
		{
			Rook &rook = dynamic_cast<Rook &>(fromPiece);
			if (rook.getSide() == Side::KingSide)
			{
				setCanCastleKingside(false, color);
				getKing(color)->setCanCastleKingside(false);
			}
			else
			{
				setCanCastleQueenside(false, color);
				getKing(color)->setCanCastleQueenside(false);
			}
		}
	}
}

void Board::updateEnPassantTargetSquare(Piece &fromPiece, Position from, Position to)
{
	if (fromPiece.getPieceType() == PieceType::Pawn && abs(from.row - to.row) == 2)
	{
		setEnPassantTargetSquare(&getSquare((from.row + to.row) / 2, from.col));
	}
	else
	{
		setEnPassantTargetSquare(nullptr);
	}
}

Square *Board::getEnPassantTargetSquare()
{
	return enPassantTargetSquare;
}

void Board::setEnPassantTargetSquare(Square *square)
{
	enPassantTargetSquare = square;
}

Position Board::convertStringToPosition(std::string position)
{
	return Position{8 - (position[1] - '0'), position[0] - 'a'};
}

std::string Board::convertPositionToString(Position position)
{
	return std::string(1, position.col + 'a') + std::to_string(8 - position.row);
}

std::array<Bitboard, 64>& Board::getAttackTable(Color color, PieceType pieceType)
{
	switch (pieceType)
	{
	case PieceType::Pawn:
		return pawnAttackTable[static_cast<int>(color)];
	case PieceType::Knight:
		return knightAttackTable;
	case PieceType::Bishop:
		return bishopAttackTable;
	case PieceType::Rook:
		return rookAttackTable;
	case PieceType::Queen:
		return queenAttackTable;
	case PieceType::King:
		return kingAttackTable;
	default:
		throw std::invalid_argument("Invalid piece type");
	}
}

int Board::getPieceCount(Color color, PieceType pieceType)
{
	return pieceCount[static_cast<int>(color)][static_cast<int>(pieceType)];
}

void Board::incrementPieceCount(Color color, PieceType pieceType)
{
	pieceCount[static_cast<int>(color)][static_cast<int>(pieceType)]++;
}

void Board::decrementPieceCount(Color color, PieceType pieceType)
{
	pieceCount[static_cast<int>(color)][static_cast<int>(pieceType)]--;
}
