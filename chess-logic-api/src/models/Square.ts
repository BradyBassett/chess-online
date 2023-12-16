import Piece from "./Piece";

export default class Square {
  constructor(public rowIndex: number, public colIndex: number, public piece: Piece | null = null) {
    this.rowIndex = rowIndex;
    this.colIndex = colIndex;
    this.piece = piece;
  }
}
