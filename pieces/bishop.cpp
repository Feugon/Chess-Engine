#include "bishop.h"
#include "basePiece.h"
#include <vector>



void Bishop::generateMoves(const std::vector<std::unique_ptr<basePiece>> &board) {

    m_possibleMoves.clear();
    // this corresponds to position shifts for a bishop
    std::vector<int> shifts = {11,9,-9,-11};
    m_possibleMoves =  slidingMoves(board,shifts);
}