#include "Board.h"
#include "MoveValidator.h"
#include <iostream>

Board::Board() {
    initialize();
}

void Board::initialize() {
    // Set up the initial board state.
    // Initialize black pieces in their starting position. 
    squares[0][0] = Piece(PieceType::Rook,Color::Black);
    squares[0][1] = Piece(PieceType::Knight,Color::Black);
    squares[0][2] = Piece(PieceType::Bishop,Color::Black);
    squares[0][3] = Piece(PieceType::Queen,Color::Black);
    squares[0][4] = Piece(PieceType::King,Color::Black);
    squares[0][5] = Piece(PieceType::Bishop,Color::Black);
    squares[0][6] = Piece(PieceType::Knight,Color::Black);
    squares[0][7] = Piece(PieceType::Rook,Color::Black);

    for(int i = 0 ; i < 8 ; ++i) {
        squares[1][i] = Piece(PieceType::Pawn,Color::Black);
    }

    // Intialize white pieces in their starting position. 
    squares[7][0] = Piece(PieceType::Rook,Color::White);
    squares[7][1] = Piece(PieceType::Knight,Color::White);
    squares[7][2] = Piece(PieceType::Bishop,Color::White);
    squares[7][3] = Piece(PieceType::Queen,Color::White);
    squares[7][4] = Piece(PieceType::King,Color::White);
    squares[7][5] = Piece(PieceType::Bishop,Color::White);
    squares[7][6] = Piece(PieceType::Knight,Color::White);
    squares[7][7] = Piece(PieceType::Rook,Color::White);

    for(int i = 0 ; i < 8 ; ++i) {
        squares[6][i] = Piece(PieceType::Pawn,Color::White);
    }

    //Setting empty squares for the rest of the board. 
    for(int i = 2 ; i < 6 ; ++i) {
        for(int j = 0 ; j < 8 ; ++j) {
            squares[i][j] = Piece();
        }
    }
}

void Board::printBoard() const {
    for(int i = 0 ; i < 8 ; ++i) {
        std::cout << (i + 1) <<"|";
        for(int j = 0; j < 8 ; ++j) {
            Piece piece = squares[i][j];
            if(piece.isEmpty()) {
                std::cout << ".";
            }
            else {
                char pieceChar = ' ';
                switch(piece.getType()) {
                    case PieceType::Pawn: pieceChar = 'P'; break;
                    case PieceType::Bishop: pieceChar = 'B'; break;
                    case PieceType::Knight: pieceChar = 'N'; break;
                    case PieceType::Rook: pieceChar = 'R'; break;
                    case PieceType::Queen: pieceChar = 'Q'; break;
                    case PieceType::King: pieceChar = 'K'; break;
                    default: break;
                }

                if(piece.getColor() == Color::Black) {
                    pieceChar = tolower(pieceChar);
                }
                std::cout << pieceChar;
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "  - - - - - - - -" << std::endl;
    std::cout << "  a b c d e f g h" << std::endl;
}

Piece Board::getPiece(int x,int y) const{
    return squares[x][y];
}

void Board::setPiece(int x,int y,Piece piece) {
    squares[x][y] = piece;
}





