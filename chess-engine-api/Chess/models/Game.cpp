#include <stdexcept>
#include <sstream>
#include "Game.h"
#include "../enums/PieceType.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "King.h"
#include "Pawn.h"

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

void Game::validateGenericMove(Position from, Position to, Piece &fromPiece, Square &toSquare)
{
	// check if it's the right turn
	if (fromPiece.getPieceColor() != activeColor)
	{
		throw std::invalid_argument("Invalid move - You can only move your own pieces");
	}

	// Check if target square is the same as the current square
	if (to == from)
	{
		throw std::invalid_argument("Invalid move - Piece must move to a different square");
	}

	// Check if target square contains a piece of the same color
	if (toSquare.getPiece() != nullptr && toSquare.getPiece()->getPieceColor() == fromPiece.getPieceColor())
	{
		throw std::invalid_argument("Invalid move - Piece cannot capture a piece of the same color");
	}

	// Check if the move is going through another piece
	if (!board.isPathClear(from, to, std::make_shared<Piece>(fromPiece)))
	{
		throw std::invalid_argument("Invalid move - Path is not clear");
	}
}

void Game::validatePawnMove(Position from, Position to, Piece &fromPiece, Square &toSquare)
{
	if (fromPiece.getPieceType() == PieceType::Pawn)
	{
		Pawn &pawn = dynamic_cast<Pawn &>(fromPiece);

		// check if the pawn is moving diagonally
		if (abs(to.col - from.col) == 1 && abs(to.row - from.row) == 1)
		{
			if (toSquare.getPiece() == nullptr)
			{
				int enPassantEligibleRow = pawn.getPieceColor() == Color::White ? 3 : 4;
				if (from.row == enPassantEligibleRow)
				{
					Square *enPassantTargetSquare = board.getEnPassantTargetSquare();
					if (enPassantTargetSquare == nullptr || to != board.getEnPassantTargetSquare()->getPosition())
					{
						throw std::invalid_argument("Invalid move - Pawn can only capture en passant if the opponents move was a pawn move of 2 squares that landed next to this pawn");
					}
				}
				else
				{
					throw std::invalid_argument("Invalid move - Pawn cannot move diagonally unless it is capturing an opponent's piece");
				}
			}
		}
		// check if the pawn is moving orthogonally
		else
		{
			if (pawn.getHasMoved())
			{
				if (!pawn.canMoveOneSquare(to))
				{
					throw std::invalid_argument("Invalid move - Pawn can only move one square forward after its first move");
				}
			}
			else
			{
				if (!pawn.canMoveOneSquare(to) && !pawn.canMoveTwoSquares(to))
				{
					throw std::invalid_argument("Invalid move - Pawn can only move two squares forward if the square in front of it is empty and it is its first move");
				}
			}
		}
	}
}

void Game::validateKingMove(Position from, Position to, Piece &fromPiece)
{
	// TODO - check for the following, moving into check, is in check, if in check can only move out of check or be protected
	if (fromPiece.getPieceType() == PieceType::King)
	{
		King &king = dynamic_cast<King &>(fromPiece);

		// If the target position is two squares away from the king then it is a castle
		if ((to.col == 2 && to.row == from.row) ||
			(to.col == 6 && to.row == from.row))
		{
			std::string errorMessage;

			if (!isValidCastle(from, to, king, errorMessage))
			{
				throw std::invalid_argument(errorMessage);
			}
		}
		// Otherwise, the king can only move one square in any direction
		else
		{
			if (abs(to.row - from.row) > 1 || abs(to.col - from.col) > 1)
			{
				throw std::invalid_argument("Invalid move - King can only move one square in any direction");
			}
		}
	}
}

// HERE IS HOW I WANT CHECK TO WORK
// AFTER A VALID MOVE IS MADE, CHECK IF THE OPPOSING KING IS IN CHECK
// ALSO, CHECK IF THE MOVE PUTS THE CURRENT KING IN CHECK
// UPDATE THE KING'S IN CHECK STATUS ONLY IN THE FIRST SCENARIO
// THE SECOND SCENARIO SHOULD THROW AND EXCEPTION

// before move validation, check if the king is in check, if it is, then the move must be to get out of check
// if the move is not to get out of check, then throw an exception
// also check if the move puts the current king in check, if it does, then throw an exception
// After the move is made, check if the opposing king is in check
// if it is, then update the king's in check status

Move Game::prepareMove(Position from, Position to, char promotion)
{
	Square &fromSquare = board.getSquare(from);
	Square &toSquare = board.getSquare(to);

	if (!fromSquare.getPiece())
	{
		throw std::invalid_argument("No piece at from position");
	}

	Piece &fromPiece = *fromSquare.getPiece();

	// Generic move checks
	validateGenericMove(from, to, fromPiece, toSquare);

	// Pawn specific checks
	validatePawnMove(from, to, fromPiece, toSquare);
	// check if move is a promotion
	handlePawnPromotion(fromPiece, fromSquare, to, from, promotion);

	// King specific checks
	validateKingMove(from, to, fromPiece);

	// If the move is a capture, store the captured piece
	std::optional<std::shared_ptr<Piece>> capturedPiece = getCapturedPiece(toSquare, from, to, fromPiece);

	// compose the move struct
	Move move = composeMoveStruct(from, to, promotion, capturedPiece);

	if (getInCheck(getActiveColor()))
	{
		// TODO - SIMULATE MOVE AND CHECK IF KING IS STILL IN CHECK - EVENTUALLY USE THE UNDO MOVE FUNCTION
		Board tempBoard = board;
		tempBoard.setupMove(move);

		if (isInCheck(getActiveColor(), tempBoard.getKing(getActiveColor())->getCurrentPosition()))
		{
			throw std::invalid_argument("Invalid move - King is still in check");
		}
	}

	return move;
}

void Game::executeMove(Move move)
{
	Piece &fromPiece = *board.getSquare(move.from).getPiece();

	// add the move to the list of moves
	addMove(move);

	// update castling availability if the move was the first move of a rook or the king
	board.updateCastlingAvailability(fromPiece);

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

	// move the piece
	board.setupMove(move);
}

void Game::postMoveChecks()
{
	// Determine the color of the other player
	Color otherColor = (getActiveColor() == Color::Black) ? Color::White : Color::Black;

	// Increment full move number if the move was made by black
	if (getActiveColor() == Color::Black)
	{
		incrementFullMoveNumber();
	}

	// Check if the move put the other king in check
	setInCheck(otherColor, isInCheck(otherColor, board.getKing(otherColor)->getCurrentPosition()));

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
	// TODO - Also be sure to update the appropriate bitboards

	if (fromPiece.canPromote(to))
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
	// regular capture
	if (toSquare.getPiece())
	{
		return toSquare.getPiece();
	}
	// en passant capture
	else if (fromPiece.getPieceType() == PieceType::Pawn && abs(from.row - to.row) == 1 && abs(from.col - to.col) == 1 && !toSquare.getPiece())
	{
		return board.getSquare(to.row + (fromPiece.getPieceColor() == Color::White ? 1 : -1), to.col).getPiece();
	}
	// no capture
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
		// TODO - Also be sure to update the appropriate bitboards
		Move lastMove = moves.back();
		moves.pop_back();

		// get the piece that was moved
		std::shared_ptr<Piece> piece = board.getSquare(lastMove.to).getPiece();

		// if the move was a capture, restore the captured piece
		if (lastMove.hasFlag(MoveFlag::StandardCapture))
		{
			// recreate the captured piece and place it on the target square
			// board.getSquare(lastMove.to).setPiece(lastMove.capturedPiece.value());
		}
		else if (lastMove.hasFlag(MoveFlag::EnPassant))
		{
			// recreate the captured piece and place it on the target square
			// board.getSquare(lastMove.to.row + (piece->getPieceColor() == Color::White ? -1 : 1), lastMove.to.col).setPiece(lastMove.capturedPiece.value());
		}

		// check if the move was a castle and restore the rook
		if (lastMove.hasFlag(MoveFlag::KingsideCastling))
		{
			board.getSquare(lastMove.to.row, 7).setPiece(board.getSquare(lastMove.to.row, 5).getPiece());
			board.getSquare(lastMove.to.row, 5).setPiece(nullptr);
		}
		else if (lastMove.hasFlag(MoveFlag::QueensideCastling))
		{
			board.getSquare(lastMove.to.row, 0).setPiece(board.getSquare(lastMove.to.row, 3).getPiece());
			board.getSquare(lastMove.to.row, 3).setPiece(nullptr);
		}

		// if the move was a promotion, remove the promoted piece
		if (lastMove.hasFlag(MoveFlag::Promotion))
		{
			board.getSquare(lastMove.to).setPiece(nullptr);
		}

		// if the move was a double pawn push, update the en passant target square, and reset pawn has moved
		if (lastMove.hasFlag(MoveFlag::PawnPush))
		{
			// TODO - update en passant target square
			// TODO - reset pawn has moved
		}

		// Move the piece back to its original position
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

bool Game::getInCheck(Color color)
{
	return color == Color::White ? whiteInCheck : blackInCheck;
}

void Game::setInCheck(Color color, bool value)
{
	if (color == Color::White)
	{
		whiteInCheck = value;
	}
	else
	{
		blackInCheck = value;
	}
}

bool Game::isInCheck(Color color, Position position)
{
	Bitboard opposingPieces = color == Color::White ? board.getBlackPiecesBitboard() : board.getWhitePiecesBitboard();

	for (int square = 0; square < 64; square++)
	{
		if (opposingPieces.getValue() & (1ULL << square))
		{
			std::shared_ptr<Piece> piece = board.getSquare(square).getPiece();
			Bitboard attackTable = board.getAttackTable(piece->getPieceColor(), piece->getPieceType())[square];
			if (attackTable.getValue() & (1ULL << position.row * 8 + position.col))
			{
				return true;
			}
		}
	}

	return false;
}

bool Game::isValidCastle(Position from, Position to, King &king, std::string &errorMessage)
{
	if (!(board.getWhiteCanCastleKingside() || board.getWhiteCanCastleQueenside() || board.getBlackCanCastleKingside() || board.getBlackCanCastleQueenside()))
	{
		errorMessage = "Invalid move - No castling rights";
		return false;
	}

	// If king is trying to castle queen side get the rook on the queen side and vice versa
	Side side = to.col == 2 ? Side::QueenSide : Side::KingSide;
	std::shared_ptr<Rook> rook = board.getRook(king.getPieceColor(), side);

	if (king.getHasMoved())
	{
		errorMessage = "Invalid move - King has already moved";
		return false;
	}
	else if (rook->getHasMoved())
	{
		std::string rookSide = side == Side::QueenSide ? "Queenside " : "Kingside ";
		errorMessage = "Invalid move - " + rookSide + "Rook has already moved";
		return false;
	}
	else if (king.getIsInCheck())
	{
		errorMessage = "Invalid move - King is in check";
		return false;
	}

	int direction = side == Side::QueenSide ? -1 : 1;
	for (int i = from.col + direction; i != rook->getCurrentPosition().col; i + direction)
	{
		Square &square = board.getSquare(from.row, i);
		// If there is a piece between the king and the rook then the king cannot castle
		if (square.getPiece() != nullptr)
		{
			errorMessage = "Invalid move - King cannot castle through other pieces";
			return false;
		}

		if (isInCheck(king.getPieceColor(), {from.row, i}))
		{
			errorMessage = "Invalid move - King cannot castle through check";
			return false;
		}
	}

	return true;
}