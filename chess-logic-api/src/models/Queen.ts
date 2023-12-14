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

    if (super.targetSquareIsDiagonal(targetSquare)) { // checks if target square is diagonal from current square
      // if there are pieces between the valid path between the current square and the target square, return false
      return super.isValidDiagonalMove(targetSquare, board)

    }
    else if (super.targetSquareIsStraight(targetSquare)) { // checks if target square is in the same row or col as current square
      // if there are pieces between the valid path between the current square and the target square, return false
      return super.isValidStraightMove(targetSquare, board)
    }
    else { // if target square is not diagonal or straight from current square, return false
      return false;
    }
  }
}
