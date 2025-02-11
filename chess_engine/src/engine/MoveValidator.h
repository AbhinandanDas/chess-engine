#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include "Board.h"
#include "Move.h"

class MoveValidator {
    public: 
    static bool isValidMove(const Board& board, const Move& move);
    static bool isPathClear(const Board& board, int fromX,int fromY,int toX, int toY);

    private: 
    // Move validation logic for each piece. 
    static bool isValidPawnMove(const Board& board,const Move& move); 
    static bool isValidRookMove(const Board& board,const Move& move);
    static bool isValidBishopMove(const Board& board,const Move& move);
    static bool isValidKnightMove(const Board& board,const Move& move);
    static bool isValidQueenMove(const Board& board,const Move& move);
    static bool isValidKingMove(const Board& board,const Move& move);
};


#endif //MOVEVALIDATOR