cmake_minimum_required(VERSION 3.10)
project(ChessEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(ChessEngine
    src/main.cpp
    src/engine/Board.cpp
    src/engine/Piece.cpp
    src/engine/MoveValidator.cpp
    src/engine/Game.cpp 
)