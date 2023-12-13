import Piece from './Piece';

export default class Square {
  public piece: Piece | null;
  constructor(piece: Piece | null) {
    this.piece = piece;
  }
}