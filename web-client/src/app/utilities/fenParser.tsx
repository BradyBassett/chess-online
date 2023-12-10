import React from "react";
import Piece from "../components/Piece";
import { SQUARE_SIZE } from "./constants";


type Pieces = (React.ReactElement | null)[]
type PieceMapping = {
  [key: string]: ["rook" | "knight" | "bishop" | "queen" | "king" | "pawn", "dark" | "light"];
};

export function parseFenPosition(fenPosition: string): Pieces {
  const pieces: Pieces = [];
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

  let numSquaresPerRow = 0;

  for (const char of fenPosition.split("")) {
    // If character is a /, start the next row, ensuring numSquaresPerRow is equal to 8
    if (char === "/"){
      if (numSquaresPerRow !== 8) {
        throw new Error("Invalid Fen Position");
      }
      numSquaresPerRow = 0;
    }
    // if the character is any digit from 1-8 add empty squares to pieces (represented as null)
    else if (isDigitFrom1To8(char)){
      numSquaresPerRow += parseInt(char);
      for (let i = 0; i < parseInt(char); i++) {
        pieces.push(null);
      }
    } 
    // If the character is not "/", a digit from 1-8, or a key in pieceMappings throw an error
    else if (!(char in pieceMappings)) {
      throw new Error("Invalid Fen Position");
    }
    // All remaining possible characters represent pieces
    else {      
      numSquaresPerRow += 1;
      const [type, color] = pieceMappings[char];
      pieces.push(<Piece size={SQUARE_SIZE} type={type} color={color}/>)
    }
  }
  return pieces;
}

export function isDigitFrom1To8(char: string): boolean {
  return /^[1-8]$/.test(char);
}
