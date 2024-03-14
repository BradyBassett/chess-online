#include <stdexcept>
#include <sstream>
#include "Game.h"
#include "../enums/PieceType.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"

Game::Game(std::vector<std::string> fenParts) : board(fenParts[0], fenParts[2], fenParts[3])
{
	parseActiveColor(fenParts[1]);
	parseHalfmoveClock(fenParts[4]);
	parseFullmoveNumber(fenParts[5]);
}

void Game::parseActiveColor(const std::string &color)
{
	activeColor = (color == "w") ? Color::White : Color::Black;
}

void Game::parseHalfmoveClock(const std::string &halfmove)
{
	halfMoveClock = std::stoi(halfmove);
}

void Game::parseFullmoveNumber(const std::string &fullmove)
{
	fullMoveNumber = std::stoi(fullmove);
}

Color Game::getActiveColor()
{
	return activeColor;
}

void Game::switchActiveColor()
{
	activeColor = (activeColor == Color::White) ? Color::Black : Color::White;
}

Board &Game::getBoard()
{
	return board;
}

std::string Game::ascii()
{
	std::string result;

	for (int i = 0; i < 8; i++)
	{
		result += "--+---+---+---+---+---+---+---+---+\n";
		result += std::to_string(8 - i) + " | ";
		for (int j = 0; j < 8; j++)
		{
			Square &square = board.getSquare(i, j);
			std::shared_ptr<Piece> piece = square.getPiece();
			result += pieceToAscii(piece);
			result += " | ";
		}
		result += "\n";
	}

	return result += "--+---+---+---+---+---+---+---+---+\n  | a | b | c | d | e | f | g | h |\n";
}

char Game::pieceToAscii(std::shared_ptr<Piece> piece)
{
	if (!piece)
	{
		return ' ';
	}

	Color pieceColor = piece->getPieceColor();

	switch (piece->getPieceType())
	{
	case PieceType::Pawn:
		return (pieceColor == Color::White) ? 'P' : 'p';
	case PieceType::Knight:
		return (pieceColor == Color::White) ? 'N' : 'n';
	case PieceType::Bishop:
		return (pieceColor == Color::White) ? 'B' : 'b';
	case PieceType::Rook:
		return (pieceColor == Color::White) ? 'R' : 'r';
	case PieceType::Queen:
		return (pieceColor == Color::White) ? 'Q' : 'q';
	case PieceType::King:
		return (pieceColor == Color::White) ? 'K' : 'k';
	default:
		return ' ';
	}
}

PieceType Game::charToPieceType(char piece)
{
	switch (piece)
	{
	case 'p':
		return PieceType::Pawn;
		break;
	case 'n':
		return PieceType::Knight;
		break;
	case 'b':
		return PieceType::Bishop;
		break;
	case 'r':
		return PieceType::Rook;
		break;
	case 'q':
		return PieceType::Queen;
		break;
	case 'k':
		return PieceType::King;
		break;
	default:
		throw std::invalid_argument("Invalid piece type");
	}
}

Move Game::composeMoveStruct(Position from, Position to, char promotion, std::optional<std::shared_ptr<Piece>> capturedPiece)
{
	Move move;
	move.color = activeColor;
	move.from = from;
	move.to = to;
	move.piece = board.getSquare(from).getPiece()->getPieceType();

	if (move.piece == PieceType::Pawn)
	{
		if (promotion != '\0')
		{
			move.setFlag(MoveFlag::Promotion);
			move.promotion = charToPieceType(promotion);
		}
		else if (abs(from.row - to.row) == 2)
		{
			move.setFlag(MoveFlag::PawnPush);
		}
	}

	if (promotion != '\0' && move.piece == PieceType::Pawn)
	{
		move.setFlag(MoveFlag::Promotion);
		move.promotion = charToPieceType(promotion);
	}

	if (capturedPiece.has_value() && capturedPiece.value()->getPieceColor() != activeColor)
	{
		if (move.piece == PieceType::Pawn && abs(from.row - to.row) == 1 && abs(from.col - to.col) == 1 && !board.getSquare(to).getPiece())
		{
			move.setFlag(MoveFlag::EnPassant);
		}
		else
		{
			move.setFlag(MoveFlag::StandardCapture);
		}
		move.capturedPiece = capturedPiece.value()->getPieceType();
	}
	else
	{
		move.setFlag(MoveFlag::NonCapture);
	}

	if (move.piece == PieceType::King && to.col > from.col)
	{
		move.setFlag(MoveFlag::KingsideCastling);
	}
	else if (move.piece == PieceType::King && to.col < from.col)
	{
		move.setFlag(MoveFlag::QueensideCastling);
	}

	return move;
}

Move Game::prepareMove(Position from, Position to, char promotion)
{
	std::string errorMessage = "Invalid Move";
	Square &fromSquare = board.getSquare(from);
	Square &toSquare = board.getSquare(to);

	if (!fromSquare.getPiece())
	{
		throw std::invalid_argument("No piece at from position");
	}

	Piece &fromPiece = *fromSquare.getPiece();

	// check if it's the right turn
	if (fromPiece.getPieceColor() != activeColor)
	{
		throw std::invalid_argument("Invalid move - You can only move your own pieces");
	}

	// check if move is valid
	if (!fromPiece.isValidMove(board, to, errorMessage))
	{
		throw std::invalid_argument(errorMessage);
	}

	// check if move is a promotion
	handlePawnPromotion(fromPiece, fromSquare, to, from, promotion);

	// If the move is a capture, store the captured piece
	std::optional<std::shared_ptr<Piece>> capturedPiece = getCapturedPiece(toSquare, from, to, fromPiece);

	// compose the move struct
	Move move = composeMoveStruct(from, to, promotion, capturedPiece);

	return move;
}

void Game::executeMove(Move move)
{
	Piece &fromPiece = *board.getSquare(move.from).getPiece();

	// add the move to the list of moves
	addMove(move);

	// update castling availability if the move was the first move of a rook or the king
	board.updateCastlingAvailability(fromPiece);

	// move the piece
	board.setupMove(move);

	// update en passant target square if the move was a double pawn push
	board.updateEnPassantTargetSquare(fromPiece, move.from, move.to);

	// increment half move clock if the move is not a pawn move or a capture
	if (fromPiece.getPieceType() != PieceType::Pawn && !move.capturedPiece.has_value())
	{
		incrementHalfMoveClock();
	}
	else
	{
		resetHalfMoveClock();
	}
}

void Game::postMoveChecks()
{
	if (activeColor == Color::Black)
	{
		// increment full move number if the move was made by black
		incrementFullMoveNumber();
		// check if the move put the white king in check
		setWhiteInCheck(isKingInCheck(Color::White));
	}
	else
	{
		// check if the move put the black king in check
		setWhiteInCheck(isKingInCheck(Color::Black));
	}

	// change turn
	switchActiveColor();
}

void Game::attemptMove(Position from, Position to, char promotion)
{
	Move move = prepareMove(from, to, promotion);
	executeMove(move);
	postMoveChecks();
}

void Game::handlePawnPromotion(Piece &fromPiece, Square &fromSquare, Position to, Position from, char promotion)
{
	if (fromPiece.getPieceType() == PieceType::Pawn && fromPiece.canPromote(to))
	{
		switch (promotion)
		{
		case 'q':
			fromSquare.setPiece(std::make_shared<Queen>(fromPiece.getPieceColor(), from));
			break;
		case 'r':
			fromSquare.setPiece(std::make_shared<Rook>(fromPiece.getPieceColor(), from));
			break;
		case 'b':
			fromSquare.setPiece(std::make_shared<Bishop>(fromPiece.getPieceColor(), from));
			break;
		case 'n':
			fromSquare.setPiece(std::make_shared<Knight>(fromPiece.getPieceColor(), from));
			break;
		default:
			throw std::invalid_argument("Invalid move - Promotion required");
		}
	}
}

std::optional<std::shared_ptr<Piece>> Game::getCapturedPiece(Square &toSquare, Position from, Position to, Piece &fromPiece)
{
	if (toSquare.getPiece())
	{
		return toSquare.getPiece();
	}
	else if (fromPiece.getPieceType() == PieceType::Pawn && abs(from.row - to.row) == 1 && abs(from.col - to.col) == 1 && !toSquare.getPiece())
	{
		return board.getSquare(to.row + (fromPiece.getPieceColor() == Color::White ? 1 : -1), to.col).getPiece();
	}
	else
	{
		return std::nullopt;
	}
}

std::vector<Move> Game::getMoves()
{
	return moves;
}

Move Game::getLastMove()
{
	return moves.back();
}

void Game::addMove(Move move)
{
	moves.push_back(move);
}

void Game::undoPreviousMove()
{
	if (moves.size() == 0)
	{
		throw std::invalid_argument("No moves found");
	}
	else
	{
		// TODO - Implement undo move
	}
}

uint8_t Game::getHalfMoveClock()
{
	return halfMoveClock;
}

uint8_t Game::getFullMoveNumber()
{
	return fullMoveNumber;
}

void Game::incrementHalfMoveClock()
{
	halfMoveClock++;
}

void Game::resetHalfMoveClock()
{
	halfMoveClock = 0;
}

void Game::incrementFullMoveNumber()
{
	fullMoveNumber++;
}

bool Game::getWhiteInCheck()
{
	return whiteInCheck;
}

bool Game::getBlackInCheck()
{
	return blackInCheck;
}

void Game::setWhiteInCheck(bool value)
{
	whiteInCheck = value;
}

void Game::setBlackInCheck(bool value)
{
	blackInCheck = value;
}

bool Game::isKingInCheck(Color color)
{
	// TODO - Implement isKingInCheck
	return false;
}