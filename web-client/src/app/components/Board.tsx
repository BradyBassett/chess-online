"use client"

import React, { useEffect, useState } from "react";
import Square from "./Square";
import { SQUARE_SIZE, STARTING_POSITION_FEN_CODE } from "../utilities/constants";
import Piece, { PieceTypes, PieceColors } from "./Piece";
import styles from "../../styles/board.module.scss";
import { Chess } from "chess.js";


export type PieceInfo = {
  type?: PieceTypes;
  color?: PieceColors;
};

type squareCoordinate = {row: number, col: number} | null;

export default function Board(): React.ReactElement {
  const chess = new Chess();
  const [board, setBoard] = useState<(PieceInfo | null)[][]>([]);
  const [selectedSquare, setSelectedSquare] = useState<squareCoordinate>(null);
  const [destinationSquare, setDestinationSquare] = useState<squareCoordinate>(null);
  
  useEffect(() => {
    if (board.length === 0) {
      setBoardStartingPosition();
    }
  }, [board]);

  useEffect(() => {
    if (selectedSquare !== null && destinationSquare !== null) {
      const selectedPiece = board[selectedSquare.row][selectedSquare.col];
      if (selectedPiece !== null) {
        updateBoard(selectedSquare, destinationSquare);
      }

      setSelectedSquare(null);
      setDestinationSquare(null);
    }
  }, [destinationSquare]);

  function setBoardStartingPosition() {
    fetch("http://localhost:3001/api/board", {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify({ fenPosition: STARTING_POSITION_FEN_CODE }),
    })
      .then(res => res.json())
      .then(data => setBoard(data))
      .catch(err => console.error("Error setting board: ", err));
  }

  function resetBoard() {
    setBoardStartingPosition();
    setSelectedSquare(null);
    setDestinationSquare(null);
  }
  
  function handleSquareClick(rowIndex: number, colIndex: number): void {
    // if selectedSquare has not been set, set selected square
    if (selectedSquare === null) {
      setSelectedSquare({ row: rowIndex, col: colIndex});
    } 
    else if (selectedSquare.row === rowIndex && selectedSquare.col === colIndex) {
      setSelectedSquare(null);
      setDestinationSquare(null);
    }
    // If selectedSquare has been set, set new square as destination square
    else {
      setDestinationSquare({ row: rowIndex, col: colIndex});
    }
  }

  function updateBoard(selectedSquare: squareCoordinate, destinationSquare: squareCoordinate): void {
    fetch("http://localhost:3001/api/board/updateBoard", {
      method: "PATCH",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify({ selectedSquare: selectedSquare, destinationSquare: destinationSquare }),
    })
      .then(res => {
        if (!res.ok) {
          throw new Error(res.statusText);
        }
        return res.json();
      })
      .then(updatedBoardData => setBoard(updatedBoardData))
      .catch(err => console.error("Error updating board", err));
  }

  function getSquareCoordinate(rowIndex: number, colIndex: number): string {
    let columnNames = ["a", "b", "c", "d", "e", "f", "g", "h"];
    let standardRowIndex = 8 - rowIndex

    return `${columnNames[colIndex]}${standardRowIndex}`;
  }

  return (
    <>
      <button onClick={() => resetBoard()}>Reset Board</button> {/* TODO - Remove this once no longer needed */}
      <div className={styles.boardContainer}>
        <div 
          className={styles.board}
          data-testid="board"
        >
          {board.map((row, rowIndex) => (
            <div key={rowIndex} className={styles.boardRow}>
              {row.map((piece: PieceInfo | null, colIndex: number) => (
                <Square 
                  key={getSquareCoordinate(rowIndex, colIndex)}
                  testid={`square-${getSquareCoordinate(rowIndex, colIndex)}`}
                  color={(rowIndex + colIndex) % 2 === 0 ? "light" : "dark"}
                  isActive={
                    selectedSquare !== null &&
                    selectedSquare.row === rowIndex &&
                    selectedSquare.col === colIndex
                  }
                  onClick={() => handleSquareClick(rowIndex, colIndex)}
                >
                  {piece ? <Piece size={SQUARE_SIZE} type={piece.type!} color={piece.color!} /> : null}
                </Square>
              ))}
            </div>
          ))}
        </div>
      </div>
    </>
  );
}
