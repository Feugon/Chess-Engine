#include "bishop.h"
#include "pieceMovement.h"
#include <vector>

//TODO make board be the first param in everything

std::vector<int> bishopMoves(int index, const std::vector<int> &board) {

    bool isWhite = board[index] > 0;
    // this corresponds to position shifts for a bishop
    std::vector<int> shifts = {11,9,-9,-11};

    return slidingMoves(board,index,isWhite,shifts);
}