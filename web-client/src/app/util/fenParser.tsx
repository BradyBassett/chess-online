import Piece from "../components/piece";
import variables from "../../styles/_variables.module.scss";


type Pieces = (React.ReactElement | null)[]
type PieceMapping = {
  [key: string]: ["rook" | "knight" | "bishop" | "queen" | "king" | "pawn", "dark" | "light"];
};

export function parseFenPosition(fenPosition: string): Pieces {
  const pieces: Pieces = [];
  const squareSize = parseFloat(variables.squareSize);
  const pieceMappings: PieceMapping = {
    r: ["rook", "dark"],
    n: ["knight", "dark"],
    b: ["bishop", "dark"],
    q: ["queen", "dark"],
    k: ["king", "dark"],
    p: ["pawn", "dark"],
    R: ["rook", "light"],
    N: ["knight", "light"],
    B: ["bishop", "light"],
    Q: ["queen", "light"],
    K: ["king", "light"],
    P: ["pawn", "light"]
  }

  for (const char of fenPosition.split("")) {
    let color: string;
    let type: string;

    if (char == "/"){
      continue;
    }
    else if (isDigitFrom1To8(char)){
      for (let i = 0; i < parseInt(char); i++) {
        pieces.push(null);
      }
    } 
    else {      // All remaining possible characters represent pieces
      const [type, color] = pieceMappings[char];
      pieces.push(<Piece size={squareSize} type={type} color={color}/>)
    }
  }
  return pieces;
}

function isDigitFrom1To8(char: string): boolean {
  return /^[1-8]$/.test(char);
}