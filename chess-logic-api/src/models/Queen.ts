import { PieceColor, PieceType } from "../Utilities/enums";
import Board from "./Board";
import Square from "./Square";
import Piece from "./Piece";


export default class Queen extends Piece {
  private pieceType = PieceType.Queen;

  constructor(color: PieceColor, currentSquare: Square) {
    super(color, currentSquare);
  }

  public isValidMove(targetSquare: Square, board: Board): boolean {
    // common piece move validation logic
    if (!super.isValidMove(targetSquare, board)) {
      return false;
    }

    if (super.targetSquareIsDiagonal(targetSquare)) {
      return super.isValidDiagonalMove(targetSquare, board)

    }
    else if (super.targetSquareIsStraight(targetSquare)) {
      return super.isValidStraightMove(targetSquare, board)
    }
    else {
      return false;
    }
  }
}
