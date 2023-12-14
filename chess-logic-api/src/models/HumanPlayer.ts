import Player from "./Player";
import { PlayerColor } from "../Utilities/enums";

export default class HumanPlayer extends Player {
  constructor(color: PlayerColor) {
    super(color);
  }
}
