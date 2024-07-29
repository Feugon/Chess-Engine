#include "queen.h"
#include "basePiece.h"
#include <vector>


std::vector<int> Queen::generateMoves(const std::vector<std::unique_ptr<basePiece>> &board) {

    // this corresponds to position shifts for a queen
    std::vector<int> shifts = {11,10,9,1,-1,-9,-10,-11};
    return slidingMoves(board,shifts);
}