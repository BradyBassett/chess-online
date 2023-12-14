import { PieceColor, PieceType } from "../Utilities/enums";
import Board from "./Board";
import Square from "./Square";
import Piece from "./Piece";


export default class Rook extends Piece {
  private pieceType = PieceType.Rook;

  constructor(color: PieceColor, currentSquare: Square) {
    super(color, currentSquare);
  }

  public getValidMoves(board: Board): Square[] {
    const validMoves: Square[] = [];
    
    return validMoves;
  }
}
