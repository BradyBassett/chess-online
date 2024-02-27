#include "Game.h"
#include "../enums/PieceType.h"
#include <stdexcept>
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"

Game::Game(std::string fenPosition) : board(fenPosition)
{
	turn = Color::White;
}

Color Game::getTurn()
{
	return turn;
}

void Game::changeTurn()
{
	turn = (turn == Color::White) ? Color::Black : Color::White;
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
	move.color = turn;
	move.from = from;
	move.to = to;
	move.piece = board.getSquare(from.row, from.col).getPiece()->getPieceType();

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

	if (capturedPiece.value() && capturedPiece.value()->getPieceColor() != turn)
	{
		if (move.piece == PieceType::Pawn && abs(from.row - to.row) == 1 && abs(from.col - to.col) == 1 && !board.getSquare(to.row, to.col).getPiece())
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

Move Game::makeMove(Position from, Position to, char promotion)
{
	std::string errorMessage = "Invalid Move";
	Square &fromSquare = board.getSquare(from.row, from.col);
	Square &toSquare = board.getSquare(to.row, to.col);

	if (!fromSquare.getPiece())
	{
		throw std::invalid_argument("No piece at from position");
	}

	Piece &fromPiece = *fromSquare.getPiece();

	// check if move is valid
	if (!fromPiece.isValidMove(*this, to, errorMessage))
	{
		throw std::invalid_argument(errorMessage);
	}

	// check if move is a promotion
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

	// If the move is a capture, store the captured piece
	std::optional<std::shared_ptr<Piece>> capturedPiece;
	if (toSquare.getPiece())
	{
		capturedPiece = toSquare.getPiece();
	}
	else if (fromPiece.getPieceType() == PieceType::Pawn && abs(from.row - to.row) == 1 && abs(from.col - to.col) == 1 && !toSquare.getPiece())
	{
		capturedPiece = board.getSquare(to.row + (fromPiece.getPieceColor() == Color::White ? -1 : 1), to.col).getPiece();
	}

	// compose the move struct
	Move move = composeMoveStruct(from, to, promotion, capturedPiece);

	// move the piece
	addMove(move);
	board.setupMove(move);

	// change turn
	changeTurn();

	return move;
}

Position Game::convertStringToPosition(std::string position)
{
	return Position{8 - (position[1] - '0'), position[0] - 'a'};
}

std::vector<Move> Game::getMoves()
{
	if (moves.size() == 0)
	{
		return moves;
	}
	else
	{
		throw std::invalid_argument("No moves found");
	}
}

Move Game::getLastMove()
{
	if (moves.size() == 0)
	{
		return moves.back();
	}
	else
	{
		throw std::invalid_argument("No moves found");
	}
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