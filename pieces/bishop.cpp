#include "bishop.h"
#include "basePiece.h"
#include <vector>



void Bishop::generateMoves(std::vector<std::unique_ptr<basePiece>> &board) {

    m_possibleMoves.clear();
    // this corresponds to position shifts for a bishop
    std::vector<int> shifts = {11,9,-9,-11};
    std::vector<int> potentialMoves = slidingMoves(board,shifts);
    for(int move: potentialMoves) {
        if(legalMove(board, m_position, move)) {
            m_possibleMoves.push_back(move);
        }
    }
}