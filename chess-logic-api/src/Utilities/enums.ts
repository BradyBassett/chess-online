export enum GameStatus {
  InProgress, // The game is currently in progress
  Check, // The current player's king is in check
  Checkmate, // The current player's king is in checkmate, meaning they have lost
  Stalemate, // The game is in a stalemate, meaning it's a draw because the current player is not in check but has no legal moves
  Draw, // The game is a draw for any other reason (e.g., insufficient material, threefold repetition, fifty-move rule)
  Resigned, // One player has resigned
  Timeout, // One player has run out of time
  Disconnected, // One player has disconnected
  Aborted, // The game was aborted
}

export enum PlayerColor { 
  Light, 
  Dark 
}

export enum PieceType {
  Pawn,
  Knight,
  Bishop,
  Rook,
  Queen,
  King
}

export enum PieceColor {
  Light,
  Dark
}

export enum MoveType {
  Normal, // A normal move
  Capture, // A capture move
  Castle, // A castle move
  EnPassant, // An en passant move
  Promotion // A move that results in a pawn promotion
}

export enum CastleType {
  KingSide, // Castle on the KingSide
  QueenSide // Castle on the QueenSide
}

export enum PromotionType {
  Knight,
  Bishop,
  Rook,
  Queen
}
