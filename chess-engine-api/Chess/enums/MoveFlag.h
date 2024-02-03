#ifndef FLAGS_H
#define FLAGS_H

enum MoveFlag {
    NonCapture,       // 0 - a non-capture
    PawnPush,         // 1 - a pawn push of two squares
    EnPassant,        // 2 - an en passant capture
    StandardCapture,  // 3 - a standard capture
    Promotion,        // 4 - a promotion
    KingsideCastling, // 5 - kingside castling
    QueensideCastling // 6 - queenside castling
};

#endif