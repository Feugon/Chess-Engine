#include "rook.h"
#include "basePiece.h"
#include <vector>



void Rook::generateMoves(std::vector<std::unique_ptr<basePiece>> &board) {

    m_possibleMoves.clear();
    // this corresponds to position shifts for a bishop
    std::vector<int> shifts = {10,1,-1,-10};
    std::vector<int> potentialMoves = slidingMoves(board,shifts);
    for(int move: potentialMoves) {
        if(legalMove(board, m_position, move)) {
            m_possibleMoves.push_back(move);
        }
    }
}

void Rook::setIndex(int index) {
    m_position = index;
    m_hasMoved = true;
}
