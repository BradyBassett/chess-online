export default interface PieceProps {
  size: number;
  color: "dark" | "light";
  type: "bishop" | "king" | "knight" | "pawn" | "queen" | "rook";
}