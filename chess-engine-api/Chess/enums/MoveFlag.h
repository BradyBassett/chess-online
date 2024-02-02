#ifndef FLAGS_H
#define FLAGS_H

enum MoveFlag {
    NonCapture,      
    PawnPush,        
    EnPassant,       
    StandardCapture, 
    Promotion,       
    KingsideCastling,
    QueensideCastling
};

#endif