"use client"

import React, { use, useEffect, useState } from "react";
import Square from "./Square";
import { SQUARE_SIZE } from "../utilities/constants";
import Piece from "./Piece";
import styles from "../../styles/board.module.scss";
import { Chess, Square as ChessSquare, PieceSymbol, Color } from "chess.js";


type BoardSquare = {
  square: ChessSquare;
  type: PieceSymbol;
  color: Color;
} | null;

type squareCoordinate = {row: number, col: number} | null;

export default function Board(): React.ReactElement {
  const [game, setGame] = useState(new Chess());
  const [selectedSquare, setSelectedSquare] = useState<squareCoordinate>(null);
  const [destinationSquare, setDestinationSquare] = useState<squareCoordinate>(null);
  const [possibleSquares, setPossibleSquares] = useState<string[]>([]);
  const [capturableSquares, setCapturableSquares] = useState<string[]>([]);

  // Attempts to move piece when destinationSquare is set
  useEffect(() => {
    if (selectedSquare !== null && destinationSquare !== null) {
      const selectedPiece = game.board()[selectedSquare.row][selectedSquare.col];
      if (selectedPiece !== null) {
        updateBoard(selectedSquare, destinationSquare);
      }

      setSelectionSquaresNull()
    }
  }, [destinationSquare]);

  function resetBoard() {
    setGame(new Chess());
    setSelectionSquaresNull()
  }
  
  function handleSquareClick(rowIndex: number, colIndex: number): void {
    // if selectedSquare has not been set, set selected square
    if (selectedSquare === null) {
      setSelectedSquare({ row: rowIndex, col: colIndex});

      calculatePossibleMoves(getSquareCoordinate(rowIndex, colIndex));
    } 
    else if (selectedSquare.row === rowIndex && selectedSquare.col === colIndex) {
      setSelectionSquaresNull()
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

  function setSelectionSquaresNull(): void {
    setSelectedSquare(null);
    setDestinationSquare(null);
    setPossibleSquares([]);
    setCapturableSquares([]);
  }

  function sanitizeMoveNotation(move: string): ChessSquare {
    let destinationSquare: ChessSquare;

    if (move === 'O-O') {
      destinationSquare = game.turn() === 'w' ? 'g1' : 'g8';
    } 
    else if (move === 'O-O-O') {
      destinationSquare = game.turn() === 'w' ? 'c1' : 'c8';
    } 
    else {
      const sanitizedMove = move.replace(/[\+#x=]/g, '');
  
      destinationSquare = sanitizedMove.slice(-2) as ChessSquare;
    }
  
    return destinationSquare;
  }

  function calculatePossibleMoves(square: ChessSquare): void {
    const moves = game.moves({ square: square, verbose: true });
    const possibleMoves = moves.filter(move => !move.flags.includes('c')).map(move => move.to);
    const possibleCaptures = moves.filter(move => move.flags.includes('c')).map(move => move.to);

    setPossibleSquares(possibleMoves);
    setCapturableSquares(possibleCaptures);
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
                  isValidMove={possibleSquares.includes(getSquareCoordinate(rowIndex, colIndex))}
                  isCapture={capturableSquares.includes(getSquareCoordinate(rowIndex, colIndex))}
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
