#include "queen.h"
#include "basePiece.h"
#include <vector>


void Queen::generateMoves( std::vector<std::unique_ptr<basePiece>> &board) {

    m_possibleMoves.clear();
    // this corresponds to position shifts for a queen
    std::vector<int> shifts = {11,10,9,1,-1,-9,-10,-11};
    std::vector<int> potentialMoves = slidingMoves(board,shifts);
    for(int move: potentialMoves) {
        if(legalMove(board, m_position, move)) {
            m_possibleMoves.push_back(move);
        }
    }
}