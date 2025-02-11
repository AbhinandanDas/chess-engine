#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Move.h"

class Game {
public: 
    Game();
    void start();
    void makeMove(const Move& move);
    void print(); 

private: 
    Board board;
    Color currentTurn;

    bool isInCheck(Color color) const;
    bool isCheckmate(Color color);
    std::pair<int,int> findKing(Color color) const;
    bool isSquareUnderAttack(int x, int y, Color attackerColor) const;
};

#endif // GAME_H