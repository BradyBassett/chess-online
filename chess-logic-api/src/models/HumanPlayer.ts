import Player from "./Player";
import { PlayerColor } from "../utils/enums";

export default class HumanPlayer extends Player {
  constructor(color: PlayerColor) {
    super(color);
  }
}
