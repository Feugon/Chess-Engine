#include "rook.h"
#include "basePiece.h"
#include <vector>



void Rook::generateMoves(const std::vector<std::unique_ptr<basePiece>> &board) {

    m_possibleMoves.clear();
    // this corresponds to position shifts for a bishop
    std::vector<int> shifts = {10,1,-1,-10};
    m_possibleMoves = slidingMoves(board,shifts);
}

void Rook::setIndex(int index) {
    m_position = index;
    m_hasMoved = true;
}
