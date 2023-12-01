import React from "react";
import Piece from "./Piece";


interface BishopProps {
  size: number;
  color: "dark" | "light";
}

export default function Bishop({ size, color }: BishopProps): React.ReactElement {
  return <Piece size={size} color={color} type="bishop" />;
}