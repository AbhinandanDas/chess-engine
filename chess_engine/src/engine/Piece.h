// piece.h
#ifndef PIECE_H
#define PIECE_H

#include <string>

enum class PieceType { Pawn,Rook,Bishop,Knight,Queen,King,None};
enum class Color { White,Black };

class Piece {
public: 
    Piece(); //default constructor
    Piece(PieceType type, Color color); // parameterized constructor
    PieceType getType() const;
    Color getColor() const;
    bool isEmpty() const;

private: 
    PieceType type;
    Color color;
};

#endif //PIECE_H 
