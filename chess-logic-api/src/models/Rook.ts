import { PieceColor, PieceType } from "../Utilities/enums";
import Board from "./Board";
import Square from "./Square";
import Piece from "./Piece";


export default class Rook extends Piece {
  private pieceType = PieceType.Rook;

  constructor(color: PieceColor, currentSquare: Square) {
    super(color, currentSquare);
  }

  public isValidMove(targetSquare: Square, board: Board): boolean {
    // common piece move validation logic
    if (!super.isValidMove(targetSquare, board)) {
      return false;
    }

    // if the target square is not in the same row or column as the current square, return false
    if (this.currentSquare.rowIndex !== targetSquare.rowIndex && this.currentSquare.colIndex !== targetSquare.colIndex) {
      return false;
    }

    // if there are pieces between the current square and the target square, return false
    if (this.currentSquare.rowIndex === targetSquare.rowIndex) { // horizontal move
      const rowStart = Math.min(this.currentSquare.colIndex, targetSquare.colIndex);
      const rowEnd = Math.max(this.currentSquare.colIndex, targetSquare.colIndex);

      for (let i = rowStart; i < rowEnd; i++) {
        if (board.getSquare(this.currentSquare.rowIndex, i).piece) {
          return false;
        }
      }
    }
    else if (this.currentSquare.colIndex === targetSquare.colIndex) { // vertical move
      const colStart = Math.min(this.currentSquare.rowIndex, targetSquare.rowIndex);
      const colEnd = Math.max(this.currentSquare.rowIndex, targetSquare.rowIndex);

      for (let i = colStart; i < colEnd; i++) {
        if (board.getSquare(i, this.currentSquare.colIndex).piece) {
          return false;
        }
      }
    }

    return true;
  }
}


// TODO - add logic for castling