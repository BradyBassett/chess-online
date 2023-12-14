import Player from "./Player";
import Square from "./Square";

export default class Move {
  constructor(public player: Player, public from: Square, public to: Square) {
    this.player = player;
    this.from = from;
    this.to = to;
  }
}
