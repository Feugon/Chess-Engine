#include "bishop.h"
#include "basePiece.h"
#include <vector>



std::vector<int> Bishop::bishopMoves(const std::vector<int> &board) {

    // this corresponds to position shifts for a bishop
    std::vector<int> shifts = {11,9,-9,-11};
    return slidingMoves(board,shifts);
}