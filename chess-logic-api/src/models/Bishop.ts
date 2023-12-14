import { PieceColor, PieceType } from "../Utilities/enums";
import Board from "./Board";
import Square from "./Square";
import Piece from "./Piece";


export default class Bishop extends Piece {
  private pieceType = PieceType.Bishop;

  constructor(color: PieceColor, currentSquare: Square) {
    super(color, currentSquare);
  }

  public isValidMove(targetSquare: Square, board: Board): boolean {
    // common piece move validation logic
    if (!super.isValidMove(targetSquare, board)) {
      return false;
    }

    // if the targetSquare is not a diagonal of currentSquare, return false
    if (Math.abs(targetSquare.rowIndex - this.currentSquare.rowIndex) !== Math.abs(targetSquare.colIndex - this.currentSquare.colIndex)) {
      return false;
    }

    // if there are pieces between the valid path between the current square and the target square, return false
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
}
