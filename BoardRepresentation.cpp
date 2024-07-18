#include <iostream>
#include "BoardRepresentation.h"




int* boardMatrix(){

    /* We are using a 10x12 matrix for the board representation
    Logic borrowed from: https://www.chessprogramming.org/10x12_Board
    Doing the same for piece locations
    */

    int boardCoordinates[120];
    int piecePositions[120];
    int backRank[8] = {4,2,3,5,6,3,2,4};


    for(int i=0; i<120; i++) {
        boardCoordinates[i] = i;

        // Should do a FEN convertor here, but for now its whatever
        if(i > 98 || i < 21) {
            piecePositions[i] = 7;
        } else if(i / 10 == 3) {
            piecePositions[i] = -1;
        } else if(i / 10 == 8) {
            piecePositions[i] = 1;
        } else if(i / 10 == 2) {
            piecePositions[i] = backRank[i % 10 - 1] * -1;
        } else if(i / 10 == 9) {
            piecePositions[i] = backRank[i % 10 - 1];
        } else {
            piecePositions[i] = 0;
        }
    }

    for(int i = 2; i<10; i++) {
        for(int j=1; j<9; j++) {
            std::cout << piecePositions[i*10 + j] << " ";
        }
        std::cout << "\n";
    }

    return piecePositions;
}
