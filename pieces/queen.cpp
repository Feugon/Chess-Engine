#include "rook.h"
#include "pieceMovement.h"
#include <vector>

//TODO make board be the first param in everything

std::vector<int> queenMoves(int index, const std::vector<int> &board) {

    bool isWhite = board[index] > 0;
    // this corresponds to position shifts for a rook
    std::vector<int> shifts = {11,10,9,1,-1,-9,-10,-11};

    return slidingMoves(board,index,isWhite,shifts);
}