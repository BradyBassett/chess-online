import Square from "../models/Square";
import Piece from "../models/Piece";
import Rook from "../models/Rook";
import Knight from "../models/Knight";
import Bishop from "../models/Bishop";
import Queen from "../models/Queen";
import King from "../models/King";
import Pawn from "../models/Pawn";
import { PieceColor } from "./enums";


const pieceTypes: { [key: string]: (square: Square) => Piece } = {
  "r": square => new Rook(PieceColor.Dark, square),
  "n": square => new Knight(PieceColor.Dark, square),
  "b": square => new Bishop(PieceColor.Dark, square),
  "q": square => new Queen(PieceColor.Dark, square),
  "k": square => new King(PieceColor.Dark, square),
  "p": square => new Pawn(PieceColor.Dark, square),
  "R": square => new Rook(PieceColor.Light, square),
  "N": square => new Knight(PieceColor.Light, square),
  "B": square => new Bishop(PieceColor.Light, square),
  "Q": square => new Queen(PieceColor.Light, square),
  "K": square => new King(PieceColor.Light, square),
  "P": square => new Pawn(PieceColor.Light, square)
};

export function parseFenPosition(fenPosition: string): Square[] {
  const squares: Square[] = [];

  let rowIndex = 0;
  let colIndex = 0;

  for (const char of fenPosition.split("")) {
    // If character is a /, start the next row, ensuring numSquaresPerRow is equal to 8
    if (char === "/"){
      if (rowIndex !== 8 || colIndex >= 7) {
        throw new Error("Invalid Fen Position");
      }
      rowIndex = 0;
      colIndex += 1;
    }
    // if the character is any digit from 1-8 add empty squares to pieces (represented as null)
    else if (isDigitFrom1To8(char)){
      for (let i = 0; i < parseInt(char); i++) {
        squares.push(new Square(rowIndex, colIndex, null));
        rowIndex += 1;
      }
    } 
    // If the character is not "/", a digit from 1-8, or a key in pieceMappings throw an error
    else if (!(char in pieceTypes)) {
      throw new Error("Invalid Fen Position");
    }
    // All remaining possible characters represent pieces
    else {
      const square = new Square(rowIndex, colIndex);
      const piece = pieceTypes[char](square);
      square.piece = piece;
      squares.push(square);
      rowIndex += 1;
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
