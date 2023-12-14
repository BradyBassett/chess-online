import Piece from './Piece';

export default class Square {
  constructor(public row: number, public col: number, public piece: Piece | null = null) {
    this.row = row;
    this.col = col;
    this.piece = piece;
  }
}
