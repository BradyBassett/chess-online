import { parseFenPosition } from "../Utilities/fenParser";
import Square from './Square';

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
}
