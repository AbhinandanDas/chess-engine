// Piece.cpp
#include "Piece.h"

// default constructor
Piece::Piece() : type(PieceType::None),color(Color::White) {}

// Parameterized constructor
Piece::Piece(PieceType type, Color color) : type(type),color(color) {}

PieceType Piece::getType() const{
    return type;
}

Color Piece::getColor() const{
    return color;
}

bool Piece::isEmpty() const {
    return type == PieceType::None;
}