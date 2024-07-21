#include "BoardRepresentation.h"
#include "pieces/queen.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> board = boardMatrix("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");


    int ix = 64;
    board[ix] = 9;
    std::vector<int> moves = queenMoves(ix,board);


    for(int move: moves) {
        board[move] = 8;
        std::cout <<move << "\n";
    }

    printBoard(board);

    return 0;
}
