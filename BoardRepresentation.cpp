#include <iostream>
#include "BoardRepresentation.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>



//TODO make the input a FEN string
//TODO pieces are setup wrong (right and left borders are 0's instead of 7's)
std::vector<int> boardMatrix(const std::string &FEN){

    /* We are using a 10x12 matrix for the board representation
    Logic borrowed from: https://www.chessprogramming.org/10x12_Board
    Doing the same for piece locations
    */

    int stringIndex = 0;
    std::vector<int> piecePositions;
    std::unordered_map<char,int> charToPieceInt = {
    {'k',-6},{'q',-5},{'r',-4},{'b',-3},{'n',-2},{'p',-1},
{'K',6},{'Q',5},{'R',4},{'B',3},{'N',2},{'P',1}
    };




    for(int i=0; i<120; i++) {
        if(i < 21 || i > 98 || i % 10 == 0 || i % 10 == 9) {
            piecePositions.push_back(7);
        } else if (std::isdigit(FEN[stringIndex])) {
            int numSpaces = FEN[stringIndex] - '0';
            stringIndex++;
            for(int j = 0; j < numSpaces; j++) {
                piecePositions.push_back(0);
            }
            i += numSpaces - 1;

            if(FEN[stringIndex] == '/') {
                stringIndex++;
            }


        } else if (FEN[stringIndex] != '/'){
            piecePositions.push_back(charToPieceInt[FEN[stringIndex]]);
            stringIndex++;

            if(FEN[stringIndex] == '/') {
                stringIndex++;
            }

        }
    }



    return piecePositions;
}


void printBoard(const std::vector<int> &board) {
    for(int i = 2; i<10; i++) {
        for(int j=1; j<9; j++) {
            std::cout << board[i*10 + j] << " ";
        }
        std::cout << "\n";
    }
}



/*
21 22 23 24 25 26 27 28
31 32 33 34 35 36 37 38
41 42 43 44 45 46 47 48
51 52 53 54 55 56 57 58
61 62 63 64 65 66 67 68
71 72 73 74 75 76 77 78
81 82 83 84 85 86 87 88
91 92 93 94 95 96 97 98
*/