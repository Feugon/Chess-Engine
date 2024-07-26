#include "king.h"
#include "basePiece.h"
#include <vector>

std::vector<int> King::generateMoves(const std::vector<int> &board) {

    std::vector<int> possibleMoves;

    // this corresponds to position shifts for a knight
    int shifts[8] = {11,10,9,1,-1,-9,-10,-11};

    for(int shift : shifts) {
        if(!isOccupiedByFriendly(board,m_position + shift)) {
            possibleMoves.push_back(m_position + shift);
        }
    }

    return possibleMoves;
}