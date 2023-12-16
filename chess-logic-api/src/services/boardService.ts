import Board from "../models/Board";


let board: Board | null = null; // TODO - this is a hacky way to do this, but it works for now, replace when I have a database

export async function createBoard(fenPosition: string): Promise<Board> {
  board = new Board(fenPosition);
  return board;
}

export async function getBoard(): Promise<Board> {
  if (!board) {
    throw new Error("Board has not been created yet");
  }

  return board;
}

export async function updateBoard(selectedSquare: {row: number, col: number}, destinationSquare: {row: number, col: number}): Promise<Board> {
  if (!board) {
    throw new Error("Board has not been created yet");
  }

  const currentSquare = board.getSquare(selectedSquare.row, selectedSquare.col);
  const piece = currentSquare.piece;

  // TODO - Add piece movement logic here
  board.getSquare(destinationSquare.row, destinationSquare.col).piece = piece;
  board.getSquare(selectedSquare.row, selectedSquare.col).piece = null;

  return board;
}
