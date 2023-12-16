import Player from "./Player";
import Square from "./Square";
import { MoveType } from "../utils/enums";

export default class Move {
  constructor(public player: Player, public from: Square, public to: Square, public type: MoveType) {
    this.player = player;
    this.from = from;
    this.to = to;
    this.type = type;
  }
}
