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
	Pawn = "pawn",
	Knight = "knight",
	Bishop = "bishop",
	Rook = "rook",
	Queen = "queen",
	King = "king"
}

export enum PieceColor {
	Light = "light",
	Dark = "dark"
}

export enum MoveType {
	Normal,
	Capture,
	Castle,
	EnPassant,
	Promotion
}

export enum CastleType {
	KingSide,
	QueenSide
}

export enum PromotionType {
	Knight,
	Bishop,
	Rook,
	Queen
}
