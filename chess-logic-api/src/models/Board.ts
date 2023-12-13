import { parseFenPosition } from "../Utilities/fenParser";
import Square from './Square';

export class Board {
  public squares: Square[][] = [];
  constructor(fenPosition: string) {
    const parsedSquares = parseFenPosition(fenPosition);
    for (let i = 0; i < parsedSquares.length; i += 8) {
      this.squares.push(parsedSquares.slice(i, i + 8));
    }
  }
}
