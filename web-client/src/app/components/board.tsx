"use client"

import React, { useState } from "react";
import styles from '../../styles/board.module.scss';
import Piece from "./piece";
import { parseFenPosition } from "../util/fenParser";
import PieceProps from "@/interfaces/PieceProps";


type Square = React.ReactElement<PieceProps> | null;

export default function Board(): React.ReactElement {
  const fenCode = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" // w KQkq - 0 1
  const startingPositions = parseFenPosition(fenCode);
  
  const [board, setBoard] = useState(() => {
    const boardArray: Square[][] = [];
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
            {row.map((square: Square, colIndex: number) => (
              <div 
                key={colIndex} 
                className={`${styles.square} ${(rowIndex + colIndex) % 2 === 0 ? styles.light : styles.dark}`}>
                  {square}
              </div>
            ))}
          </div>
        ))}
      </div>
    </div>
  );
}
