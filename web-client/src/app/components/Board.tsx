"use client"

import React, { Children, useState } from "react";
import { parseFenPosition } from "../util/fenParser";
import Square from "./Square";
import { PieceProps } from "../components/Piece";

import styles from '../../styles/board.module.scss';


export type PossiblePiece = React.ReactElement<PieceProps> | null;

export default function Board(): React.ReactElement {
  const fenCode = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" // w KQkq - 0 1
  const startingPositions = parseFenPosition(fenCode);
  
  const [board, setBoard] = useState(() => {
    const boardArray: PossiblePiece[][] = [];
    for (let i = 0; i < startingPositions.length; i += 8) {
      boardArray.push(startingPositions.slice(i, i + 8));
    }
    return boardArray;
  });

  return (
    <div className={styles.boardContainer}>
      <div className={styles.board}>
        {board.map((row, rowIndex) => (
          <div key={rowIndex} className={styles.boardRow}>
            {row.map((piece: PossiblePiece, colIndex: number) => (
              <Square 
                key={colIndex} 
                color={(rowIndex + colIndex) % 2 === 0 ? "light" : "dark"}
              >
                {piece}
              </Square>
            ))}
          </div>
        ))}
      </div>
    </div>
  );
}
