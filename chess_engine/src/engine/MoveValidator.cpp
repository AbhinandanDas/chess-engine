#include "MoveValidator.h"
#include "Board.h"
#include <iostream>
bool MoveValidator::isValidMove(const Board& board,const Move& move){
    // Implement move validation logic(check rules,collisions,etc)
    int fromX = move.fromX;
    int fromY = move.fromY;
    int toX = move.toX;
    int toY = move.toY;


    // 1. Check if the move is within the board limits. 
    if(fromX < 0 || fromX >= 8 || fromY < 0 || fromY >= 8 || toX < 0 || toX >= 8 || toY < 0 || toY >= 8) {
        return false;
    }
    
    // 2. Get the piece at the source and the destination. 
    Piece sourcePiece = board.getPiece(fromX,fromY);
    Piece destPiece = board.getPiece(toX,toY);

    // 3. If there is no piece at the source. 
    if(sourcePiece.isEmpty()) {
        return false;
    }

    // 4. Prevent moving the piece to the same location.
    if(fromX == toX && fromY == toY) {
        return false;
    }

    // 5. Prevent from capturing piece of same color.
    if(!destPiece.isEmpty() && sourcePiece.getColor() == destPiece.getColor()) {
        return false;
    }

    // 6. Check for piece specific movement logic(example for different pieces).
    switch(sourcePiece.getType()) {
        case PieceType::Pawn: 
            std::cout << "Piece is a pawn." << std::endl;
            return isValidPawnMove(board,move);
        case PieceType::Rook: 
            return isValidRookMove(board,move);
        case PieceType::Knight: 
            return isValidKnightMove(board,move);
        case PieceType::Bishop: 
            return isValidBishopMove(board,move);
        case PieceType::Queen: 
            return isValidQueenMove(board,move);
        case PieceType::King: 
            return isValidKingMove(board,move);
        default: 
            return false;
    }

    return true;

}

bool MoveValidator::isPathClear(const Board& board,int fromX,int fromY, int toX, int toY) {
    int dx = toX - fromX;
    int dy = toY - fromY;
    int steps = std::max(std::abs(dx),std::abs(dy));
    int xStep = dx/steps;
    int yStep = dy/steps;

    for(int i = 1; i < steps ; ++i) {
        int x = fromX + (i * xStep);
        int y = fromY + (i * yStep);
        if(!board.getPiece(x,y).isEmpty()) {
            return false;
        }
    }

    return true;
}

bool MoveValidator::isValidPawnMove(const Board& board,const Move& move) {
    int fromX = move.fromX;
    int fromY = move.fromY;
    int toX = move.toX;
    int toY = move.toY;

    Piece piece = board.getPiece(fromX,fromY);

    int direction = (piece.getColor() == Color::White) ? -1 : 1;
    
    // Check for basic forward move. 
    if(fromY == toY && (toX == fromX + direction)) {
        std::cout << "1 step" << std::endl;
        return board.getPiece(toX,toY).isEmpty();
    }

    // Check for initial 2 square move. 
    if((fromY == toY) && (toX == fromX + (2 * direction)) && ((piece.getColor() == Color::White) ? 6 : 1)) {
        std::cout << "2 step" << std::endl;
        return isPathClear(board,move.fromX,move.fromY,move.toX,move.toY);
    }

    // Check for diagonal capture. 
    if((toX == fromX + direction) && ((toY == fromY + 1) || (toY == fromY - 1))) {
        std::cout << "Capture" << std::endl;
        return !board.getPiece(toX,toY).isEmpty() && (board.getPiece(fromX,fromY).getColor() != board.getPiece(toX,toY).getColor());
    }

    return false;

}

bool MoveValidator::isValidRookMove(const Board& board,const Move& move) {
    int dx = move.toX - move.fromX;
    int dy = move.toY - move.toX;

    // Rook can only move in along a file or rank. 
    if(dx!=0 && dy!=0) {
        return false;
    }
    return isPathClear(board,move.fromX,move.fromY, move.toX,move.toY);
}
bool MoveValidator::isValidBishopMove(const Board& board,const Move& move) {
    int dx = std::abs(move.toX - move.fromX);
    int dy = move.toY - move.fromY;

    // Bishop diagonal movement meaning, same distance moved along rank and file. 
    if(dx!=dy) {
        return false;
    }
    
    return isPathClear(board,move.fromX,move.fromY,move.toX,move.toY);
}
bool MoveValidator::isValidKnightMove(const Board& board,const Move& move) {
    int dx = std::abs(move.toX - move.fromX);
    int dy = std::abs(move.toY - move.fromY);

    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}
bool MoveValidator::isValidQueenMove(const Board& board,const Move& move) {
    int dx = std::abs(move.toX - move.fromX);
    int dy = std::abs(move.toY - move.fromY);
    
    return (dx == 0 || dy == 0 || dx == dy) && (isPathClear(board,move.fromX,move.fromY,move.toX,move.toY)); 
}
bool MoveValidator::isValidKingMove(const Board& board,const Move& move) {
    int dx = std::abs(move.toX - move.fromX);
    int dy = std::abs(move.toY - move.fromY);

    return (dx <= 1) && (dy <=1);
}


