"use client"

import React, { useState } from "react";
import { parseFenPosition } from "../util/fenParser";
import Square from "./Square";
import { PieceProps } from "../components/Piece";

import styles from '../../styles/board.module.scss';


export type PossiblePiece = React.ReactElement<PieceProps> | null;

export default function Board(): React.ReactElement {
  const [board, setBoard] = useState(setStartingPositions());

  const [selectedSquare, setSelectedSquare] = useState<number[]>([]);
  const [destinationSquare, setDestinationSquare] = useState<number[]>([]);

  function resetBoard() {
    setBoard(setStartingPositions());
  }

  function setStartingPositions() {
    const fenCode = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" // w KQkq - 0 1
    const startingPositions = parseFenPosition(fenCode);

    const boardArray: PossiblePiece[][] = [];
    for (let i = 0; i < startingPositions.length; i += 8) {
      boardArray.push(startingPositions.slice(i, i + 8));
    }

    return boardArray;
  }

  function handleSquareClick(rowIndex: number, colIndex: number) {
    // if selectedSquare has not been set, set selected square
    if (selectedSquare.length === 0) {
      setSelectedSquare([rowIndex, colIndex]);
    } 
    // If selectedSquare has been set, set new square as destination square
    else {
      setDestinationSquare([rowIndex, colIndex])
      const selectedPiece = board[selectedSquare[0]][selectedSquare[1]];

      // only update the square if selectedSquare is not null
      if (selectedPiece !== null) {
        updateSquare(selectedSquare[0], selectedSquare[1], null);
        updateSquare(rowIndex, colIndex, selectedPiece);
      }

      setSelectedSquare([]);
      setDestinationSquare([]);
    }
  }

  function updateSquare(rowIndex: number, colIndex: number, piece: PossiblePiece) {
    setBoard(prevBoard => {
      const newBoard = [...prevBoard];
      newBoard[rowIndex] = [...prevBoard[rowIndex]];
      newBoard[rowIndex][colIndex] = piece;

      return newBoard;
    })
  }

  return (
    <>
      <button onClick={() => resetBoard()}>Reset Board</button>
      <div className={styles.boardContainer}>
        <div className={styles.board}>
          {board.map((row, rowIndex) => (
            <div key={rowIndex} className={styles.boardRow}>
              {row.map((piece: PossiblePiece, colIndex: number) => (
                <Square 
                  key={colIndex} 
                  color={(rowIndex + colIndex) % 2 === 0 ? "light" : "dark"}
                  isActive={
                    selectedSquare[0] === rowIndex &&
                    selectedSquare[1] === colIndex
                  }
                  onClick={() => handleSquareClick(rowIndex, colIndex)}
                >
                  {piece}
                </Square>
              ))}
            </div>
          ))}
        </div>
      </div>
    </>
  );
}
