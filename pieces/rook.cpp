#include "rook.h"
#include "basePiece.h"
#include <vector>



void Rook::generateMoves(std::vector<std::unique_ptr<basePiece>> &board) {

    m_possibleMoves.clear();
    // this corresponds to position shifts for a bishop
    std::vector<int> shifts = {10,1,-1,-10};
    m_possibleMoves = slidingMoves(board,shifts);
}

void Rook::move(int index) {
    m_position = index;
    m_timesMoved++;
    basePiece::m_enPassantPosition = 0;
}
