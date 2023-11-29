"use client"

import React, { useState } from "react";
import styles from '../../styles/board.module.scss';


interface Square {
  piece: string | null;
}

export default function Board() {
  const [board, setBoard] = useState(Array(8).fill(Array(8).fill(null)));

  return (
    <div className={styles.boardContainer}>
      <div className={styles.board}>
        {board.map((row, rowIndex) => (
          <div key={rowIndex} className={styles.boardRow}>
            {row.map((square: Square, colIndex: number) => (
              <div 
                key={colIndex} 
                className={`${styles.square} ${(rowIndex + colIndex) % 2 === 0 ? styles.light : styles.dark}`}>
              </div>
            ))}
          </div>
        ))}
      </div>
    </div>
  );
}