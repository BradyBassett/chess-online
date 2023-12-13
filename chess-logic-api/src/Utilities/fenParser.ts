import Square from "../models/Square";
import Rook from "../models/Rook";
import Knight from "../models/Knight";
import Bishop from "../models/Bishop";
import Queen from "../models/Queen";
import King from "../models/King";
import Pawn from "../models/Pawn";


type PieceType = {
  r: Rook;
  n: Knight;
  b: Bishop;
  q: Queen;
  k: King;
  p: Pawn;
  R: Rook;
  N: Knight;
  B: Bishop;
  Q: Queen;
  K: King;
  P: Pawn;
  [key: string]: Rook | Knight | Bishop | Queen | King | Pawn;
};

const pieceTypes: PieceType = {
  "r": new Rook("dark"),
  "n": new Knight("dark"),
  "b": new Bishop("dark"),
  "q": new Queen("dark"),
  "k": new King("dark"),
  "p": new Pawn("dark"),
  "R": new Rook("light"),
  "N": new Knight("light"),
  "B": new Bishop("light"),
  "Q": new Queen("light"),
  "K": new King("light"),
  "P": new Pawn("light")
};

export function parseFenPosition(fenPosition: string) {
  const squares: Square[] = [];

  let numSquares = 0;
  for (const char of fenPosition.split("")) {
    // If character is a /, start the next row, ensuring numSquaresPerRow is equal to 8
    if (char === "/"){
      if (numSquares !== 8) {
        throw new Error("Invalid Fen Position");
      }
      numSquares = 0;
    }
    // if the character is any digit from 1-8 add empty squares to pieces (represented as null)
    else if (isDigitFrom1To8(char)){
      numSquares += parseInt(char);
      for (let i = 0; i < parseInt(char); i++) {
        squares.push(new Square(null));
      }
    } 
    // If the character is not "/", a digit from 1-8, or a key in pieceMappings throw an error
    else if (!(char in pieceTypes)) {
      throw new Error("Invalid Fen Position");
    }
    // All remaining possible characters represent pieces
    else {      
      numSquares += 1;
      squares.push(new Square(pieceTypes[char]));
    }
  }
  return squares;
}

export function parseFenActiveColor(fenActiveColor: string) {
  // TODO - implement
}

export function parseFenCastling(fenCastling: string) {
  // TODO - implement
}

export function parseFenEnPassant(fenEnPassant: string) {
  // TODO - implement
}

export function parseFenHalfMoveClock(fenHalfMoveClock: string) {
  // TODO - implement
}

export function parseFenFullMoveNumber(fenFullMoveNumber: string) {
  // TODO - implement
}

export function isDigitFrom1To8(char: string): boolean {
  return /^[1-8]$/.test(char);
}
