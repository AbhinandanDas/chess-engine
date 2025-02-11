// Game.cpp

#include "Game.h"
#include "MoveValidator.h"
#include <iostream>

Game::Game() : currentTurn(Color::White) {
    board.initialize();
}

void Game::start() {
    std::cout << "Welcome to Chess Engine" << std::endl;
    std::cout << "Type your moves in format 'e2e4'." << std::endl;
    board.printBoard();
}

void Game::print() {
    board.printBoard();
}

void Game::makeMove(const Move& move) {
    // Move is invalid.

    std::cout << move.fromX << "," << move.fromY << " to " << move.toX << "," << move.toY << std::endl;
    if(!MoveValidator::isValidMove(board,move)) {
        std::cout << "Invalid Move" << std::endl;
    }
    // Update the board and switch the turns.
    else {
        Piece piece = board.getPiece(move.fromX,move.fromY);
        std::cout << "Making move.." << std::endl;
        board.setPiece(move.toX,move.toY,piece); //  Move piece to destination location.
        board.setPiece(move.fromX,move.fromY,Piece(PieceType::None,Color::White));

        //Switch turns. 
        currentTurn = (currentTurn == Color::White) ? Color::Black : Color::White; 
        
        //Check for checkmate
        if(isCheckmate(currentTurn)) {
            std::cout << "Checkmate for " << (currentTurn == Color::White ? "Black" : "White") << " Wins" << std::endl;
            exit(0);
        }

        //Check for check
        if(isInCheck(currentTurn)) {
            std::cout << "Check" << std::endl;
        }
        
    }   
}

bool Game::isInCheck(Color color) const {
    auto [kingX,kingY] = findKing(color);
    return isSquareUnderAttack(kingX,kingY,(color == Color::White) ? Color::Black : Color::White);
}

bool Game::isCheckmate(Color color){
    // If the king is not in check then not a checkmate.
    if(!isInCheck(color)) {
        return false;
    }

    // Try all possible moves to see if it can get current player out of check. 
    for(int x = 0 ; x < 8 ; ++x) {
       for(int y = 0 ; y < 8 ; ++y) {
            Piece piece = board.getPiece(x,y);
            if(piece.getColor() == color) {
                for(int tx = 0 ; tx < 8 ; ++tx) {
                    for(int ty = 0 ; ty < 8 ; ++ty) {
                        Move move{x,y,tx,ty};
                        if(MoveValidator::isValidMove(board,move)) {
                            // Simulate the move. 
                            Piece capturedPiece = board.getPiece(tx,ty);
                            board.setPiece(tx,ty,piece);
                            board.setPiece(x,y,Piece());

                            bool isStillInCheck = isInCheck(color);

                            // undo the move. 
                            board.setPiece(x,y,piece);
                            board.setPiece(tx,ty,capturedPiece);

                            if(!isStillInCheck) {
                                return false;
                            }
                        }
                    }
                }
            }
       } 
    }

    return true;
}

std::pair<int,int> Game::findKing(Color color) const {
    for(int x = 0 ; x < 8 ; ++x) {
        for(int y = 0 ; y < 8 ; ++y) {
            Piece piece = board.getPiece(x,y);
            if((!piece.isEmpty()) && (piece.getType() == PieceType::King) && (piece.getColor() == color)) {
                return {x,y};
            }
        }
    }
    throw std::runtime_error("King not found!");
}

bool Game::isSquareUnderAttack(int x, int y , Color attackerColor) const {
    for(int tx = 0 ; tx < 8 ; ++tx) {
        for(int ty = 0 ; ty < 8 ; ++ty) {
            Piece piece = board.getPiece(tx,ty);
            if(piece.getColor() == attackerColor) {
                Move move{tx,ty,x,y};
                if(MoveValidator::isValidMove(board,move)) {
                    return true; // the square is under attack. 
                }
            }
        }
    }
    return false;
}