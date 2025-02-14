// Game.cpp

#include "Game.h"
#include "MoveValidator.h"
#include <iostream>

Game::Game() : currentTurn(Color::White) {
    board.initialize();
}

Move Game::stringToMoveConverter(const std::string& move) {
        Move m;
        m.fromY = move[0] - 'a';
        m.fromX = move[1] - '1';

        m.toY = move[2] - 'a';
        m.toX = move[3] - '1';

        return m;
}

void checkForQuit(const std::string& input) {
    if(input == "quit") exit(0);
}

void Game::start() {
    std::cout << "Welcome to Chess Engine" << std::endl;
    std::cout << "Type your moves in format 'e2e4'." << std::endl;
    print();
    std::string inputMove;
    while(true) {
        std::cout << (currentTurn == Color::White ? "White" : "Black") << " player turn. Enter your move" << std::endl;
        std::cin >> inputMove;
        
        checkForQuit(inputMove);

        Move move = stringToMoveConverter(inputMove);
        // If the current player does not make a valid move, then ask them to make valid move. 
        while(!preMoveValidations(move)) {
           std::cout << (currentTurn == Color::White ? "White" : "Black") << " player turn. Enter a valid move" << std::endl;
           std::cin >> inputMove;
           checkForQuit(inputMove);
           move = stringToMoveConverter(inputMove);
        }

         makeMove(move);

        // Check for checkmate.
        if(isCheckmate((currentTurn == Color::White) ? Color::Black : Color::White)) {
            std::cout << "Checkmate!" << (currentTurn == Color::White ? "White" : "Black") << " wins" << std::endl;
            break;
        }

        // TODO: Check for stalemate.

        print();
        
        // Switch turns. 
        currentTurn = (currentTurn == Color::White) ? Color::Black : Color::White;
    }
}

void Game::print() {
    board.printBoard();
}

bool Game::preMoveValidations(const Move& move) {
   // The move is not a valid move. 
   if(!MoveValidator::isValidMove(board,move)) {
        std::cout << "This move cannot be made!" << std::endl;
        return false;
   }
   return true;
}

void Game::makeMove(const Move& m) {
   

   // Make the move. 
   Piece piece = board.getPiece(m.fromX,m.fromY);
   Piece capturedPiece = board.getPiece(m.toX,m.toY);
   board.setPiece(m.toX,m.toY,piece);
   board.setPiece(m.fromX,m.fromY,Piece());

   // Check for check 
   if(isInCheck(currentTurn)) {
        //Undo the move. 
        board.setPiece(m.fromX,m.fromY,piece);
        board.setPiece(m.toX,m.toY,capturedPiece);

        std::cout << "Not a valid move, current player's king would be in check" << std::endl;
        return;
   }

}

bool Game::isInCheck(Color color) const {
    std::pair<int,int> kingCoordinates = findKing(color);
    int kingX = kingCoordinates.first;
    int kingY = kingCoordinates.second;
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
                return std::make_pair(x,y);
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