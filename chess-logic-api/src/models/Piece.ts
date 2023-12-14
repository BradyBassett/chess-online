import { PieceColor } from "../Utilities/enums";
import Board from "./Board";

import Square from "./Square";


export default abstract class Piece {
  protected hasMoved: boolean = false;
  protected isCaptured: boolean = false;

  constructor(public color: PieceColor, public currentSquare: Square) {
    this.color = color;
    this.currentSquare = currentSquare;
  }

  protected isValidMove(targetSquare: Square, board: Board): boolean {
    // if target square is the same as current square, return false
    if (this.currentSquare === targetSquare) {
      return false;
    }

    // if the target square is occupied by a piece of the same color, return false
    if (targetSquare.piece && targetSquare.piece.color === this.color) {
      return false;
    }
    
    return true;
  }

  // only call these methods if in Bishop or Queen
  protected isValidDiagonalMove(targetSquare: Square, board: Board): boolean {
    const rowStep = (targetSquare.rowIndex - this.currentSquare.rowIndex) > 0 ? 1 : -1;
    const colStep = (targetSquare.colIndex - this.currentSquare.colIndex) > 0 ? 1 : -1;
    
    let i = this.currentSquare.rowIndex + rowStep
    let j = this.currentSquare.colIndex + colStep
    while ((rowStep > 0 ? i < targetSquare.rowIndex : i > targetSquare.rowIndex) && 
           (colStep > 0 ? j < targetSquare.colIndex : j > targetSquare.colIndex)) {
        
      if (board.getSquare(i, j).piece) {
        return false;
      }
            
      i += rowStep;
      j += colStep;
    }
    
    return true;
  }

  protected targetSquareIsDiagonal(targetSquare: Square): boolean {
    return Math.abs(targetSquare.rowIndex - this.currentSquare.rowIndex) !== Math.abs(targetSquare.colIndex - this.currentSquare.colIndex);
  }

  // only call these methods if in Rook or Queen
  protected isValidStraightMove(targetSquare: Square, board: Board): boolean {
    if (this.currentSquare.rowIndex === targetSquare.rowIndex) { // horizontal move
      const rowStart = Math.min(this.currentSquare.colIndex, targetSquare.colIndex);
      const rowEnd = Math.max(this.currentSquare.colIndex, targetSquare.colIndex);

      for (let i = rowStart + 1; i < rowEnd - 1; i++) {
        if (board.getSquare(this.currentSquare.rowIndex, i).piece) {
          return false;
        }
      }
    }
    else if (this.currentSquare.colIndex === targetSquare.colIndex) { // vertical move
      const colStart = Math.min(this.currentSquare.rowIndex, targetSquare.rowIndex);
      const colEnd = Math.max(this.currentSquare.rowIndex, targetSquare.rowIndex);

      for (let i = colStart + 1; i < colEnd - 1; i++) {
        if (board.getSquare(i, this.currentSquare.colIndex).piece) {
          return false;
        }
      }
    }
    
    return true;
  }

  protected targetSquareIsStraight(targetSquare: Square): boolean {
    return this.currentSquare.rowIndex === targetSquare.rowIndex || this.currentSquare.colIndex === targetSquare.colIndex;
  }
}
