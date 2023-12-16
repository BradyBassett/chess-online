import { parseFenPosition } from "../utils/fenParser";
import Square from "./Square";

export type PieceInfo = {
  type?: string;
  color?: string;
};

export default class Board {
  public squares: Square[][] = [];
  constructor(fenPosition: string) {
    this.setStartingPosition(fenPosition);
  }

  public setStartingPosition(fenPosition: string): void {
    this.squares = [];
    const parsedSquares = parseFenPosition(fenPosition);
    for (let i = 0; i < parsedSquares.length; i += 8) {
      this.squares.push(parsedSquares.slice(i, i + 8));
    }
  }

  public getSquare(rowIndex: number, colIndex: number): Square {
    return this.squares[rowIndex][colIndex];
  }

  public toJSON(): (PieceInfo | null)[][] {
    return this.squares.map(row => 
      row.map(square => 
        square.piece ? { 
          type: square.piece.pieceType.toString(), 
          color: square.piece.color.toString()
        } : null
      )
    );
  }
}
