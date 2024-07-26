#include "rook.h"
#include "basePiece.h"
#include <vector>



std::vector<int> Rook::generateMoves(const std::vector<int> &board) {

    // this corresponds to position shifts for a bishop
    std::vector<int> shifts = {10,1,-1,-10};
    return slidingMoves(board,shifts);
}