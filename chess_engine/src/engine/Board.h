// Board.h
#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Move.h"
#include <array>


class Board {
public: 
    Board();
    void initialize();
    Piece getPiece(int x,int y) const;
    void setPiece(int x, int y, Piece piece);
    void printBoard() const;

private: 
    std::array<std::array<Piece,8>,8> squares;
};


#endif //BOARD_H