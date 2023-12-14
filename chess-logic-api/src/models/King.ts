import { PieceColor, PieceType } from "../Utilities/enums";
import Board from "./Board";
import Square from "./Square";
import Piece from "./Piece";


export default class King extends Piece {
  private pieceType = PieceType.King;

  constructor(color: PieceColor, currentSquare: Square) {
    super(color, currentSquare);
  }

  public isValidMove(targetSquare: Square, board: Board): boolean {
    // common piece move validation logic
    if (!super.isValidMove(targetSquare, board)) {
      return false;
    }

    // moving ↑ 1
    if (targetSquare.rowIndex === this.currentSquare.rowIndex + 1 && targetSquare.colIndex === this.currentSquare.colIndex) {
      return true;
    }
    // moving ↗ 1
    else if (targetSquare.rowIndex === this.currentSquare.rowIndex + 1 && targetSquare.colIndex === this.currentSquare.colIndex + 1) {
      return true;
    }
    // moving → 1
    else if (targetSquare.rowIndex === this.currentSquare.rowIndex && targetSquare.colIndex === this.currentSquare.colIndex + 1) {
      return true;
    }
    // moving ↘ 1
    else if (targetSquare.rowIndex === this.currentSquare.rowIndex - 1 && targetSquare.colIndex === this.currentSquare.colIndex + 1) {
      return true;
    }
    // moving ↓ 1
    else if (targetSquare.rowIndex === this.currentSquare.rowIndex - 1 && targetSquare.colIndex === this.currentSquare.colIndex) {
      return true;
    }
    // moving ↙ 1
    else if (targetSquare.rowIndex === this.currentSquare.rowIndex - 1 && targetSquare.colIndex === this.currentSquare.colIndex - 1) {
      return true;
    }
    // moving ← 1
    else if (targetSquare.rowIndex === this.currentSquare.rowIndex && targetSquare.colIndex === this.currentSquare.colIndex - 1) {
      return true;
    }
    // moving ↖ 1
    else if (targetSquare.rowIndex === this.currentSquare.rowIndex + 1 && targetSquare.colIndex === this.currentSquare.colIndex - 1) {
      return true;
    }

    return false;
  }
}
