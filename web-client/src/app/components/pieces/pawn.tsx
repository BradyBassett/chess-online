import React from "react";
import Piece from "./Piece";


interface PawnProps {
  size: number;
  color: "dark" | "light";
}

export default function Pawn({ size, color }: PawnProps): React.ReactElement {
  return <Piece size={size} color={color} type="pawn" />;
}