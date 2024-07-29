cmake_minimum_required(VERSION 3.10)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

# Path to SFML
set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")


# Find SFML package
find_package(SFML 2.5 COMPONENTS system window network audio REQUIRED)

if (SFML_FOUND)
    # Add executable target
    add_executable(Chess main.cpp BoardRepresentation.cpp pieces/basePiece.cpp
            pieces/pawn.cpp
            pieces/pawn.h
            pieces/knight.cpp
            pieces/knight.h
            pieces/bishop.cpp
            pieces/bishop.h
            pieces/rook.cpp
            pieces/rook.h
            pieces/queen.cpp
            pieces/queen.h
            GameOutput/gameClass.cpp
            GameOutput/gameClass.h
            GameOutput/gameClass.cpp
            constants.h
            pieces/king.cpp
            pieces/king.h
            pieces/padding.h
    )

    # Specify include directories
    target_include_directories(Chess PRIVATE ${SFML_INCLUDE_DIRS})

    # Link SFML libraries
    target_link_libraries(Chess PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
else()
    message(FATAL_ERROR "SFML library not found")
endif()
