"use client"

import React, { use, useEffect, useState } from "react";
import Square from "./Square";
import { SQUARE_SIZE } from "../utilities/constants";
import Piece from "./Piece";
import styles from "../../styles/board.module.scss";
import { Chess, Square as ChessSquare, PieceSymbol, Color } from "chess.js";


export type BoardSquare = {
  square: ChessSquare;
  type: PieceSymbol;
  color: Color;
} | null;

type squareCoordinate = {row: number, col: number} | null;

export default function Board(): React.ReactElement {
  const [game, setGame] = useState(new Chess());
  const [selectedSquare, setSelectedSquare] = useState<squareCoordinate>(null);
  const [destinationSquare, setDestinationSquare] = useState<squareCoordinate>(null);

  useEffect(() => {
    if (selectedSquare !== null && destinationSquare !== null) {
      const selectedPiece = game.board()[selectedSquare.row][selectedSquare.col];
      if (selectedPiece !== null) {
        updateBoard(selectedSquare, destinationSquare);
      }

      setSelectedSquare(null);
      setDestinationSquare(null);
    }
  }, [destinationSquare]);

  function resetBoard() {
    setGame(new Chess());
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
    const selectedSquareCoordinate = getSquareCoordinate(selectedSquare!.row, selectedSquare!.col);
    const destinationSquareCoordinate = getSquareCoordinate(destinationSquare!.row, destinationSquare!.col);

    try {
      game.move({
        from: selectedSquareCoordinate,
        to: destinationSquareCoordinate
      });
    }
    catch (error) {
      console.error(error);
      return;
    }
  }

  function getSquareCoordinate(rowIndex: number, colIndex: number): ChessSquare {
    const columnNames = ["a", "b", "c", "d", "e", "f", "g", "h"];
    const standardRowIndex = 8 - rowIndex

    return `${columnNames[colIndex]}${standardRowIndex}` as ChessSquare;
  }

  return (
    <>
      <button onClick={() => resetBoard()}>Reset Board</button> {/* TODO - Remove this once no longer needed */}
      <div className={styles.boardContainer}>
        <div 
          className={styles.board}
          data-testid="board"
        >
          {game.board().map((row, rowIndex) => (
            <div key={rowIndex} className={styles.boardRow}>
              {row.map((square: BoardSquare, colIndex: number) => (
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
                  {square ? <Piece size={SQUARE_SIZE} type={square.type!} color={square.color!} /> : null}
                </Square>
              ))}
            </div>
          ))}
        </div>
      </div>
    </>
  );
}
