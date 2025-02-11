// main.cpp
#include <iostream>
#include "engine/Game.h"

Move getPlayerMove() {
    std::string moveInput;
    std::cout << "Enter your move: (e2 e4)";
    std::getline(std::cin,moveInput);

    Move move; 
    move.fromY = moveInput[0] - 'a'; 
    move.fromX = moveInput[1] - '1'; // e2 -> 4,1

    move.toY = moveInput[3] - 'a';
    move.toX = moveInput[4] - '1'; // e4 -> 4,3

    return move;
}

int main() {
    Game game;
    game.start();

    bool gameOver = false;
    while(!gameOver) {
        game.print();
        Move move;
        move = getPlayerMove();
        
    }



    // std::string input;
    // while(true) {
    //     std::cout << "Enter a move or enter 'quit' to exit ";
    //     std::cin >> input;

    //     if(input == "quit") break;

    //     // Process the move 
    //     std::cout << "You entered: " << input << std::endl;
    //     Move move;
    //     move.fromX = 0;
    //     move.fromY = 0;
    //     move.toX = 3;
    //     move.toY = 0;
    //     game.makeMove(move);
    //     game.print();
    // }
    return 0;
}