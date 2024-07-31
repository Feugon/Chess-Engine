#include "knight.h"
#include "basePiece.h"
#include <vector>
#include <iostream>


void Knight::generateMoves(std::vector<std::unique_ptr<basePiece>> &board) {
    m_possibleMoves.clear();
    // this corresponds to position shifts for a knight
    int shifts[8] = {21,19,12,8,-21,-19,-12,-8};

    for(int shift : shifts) {
        if(!isOccupiedByFriendly(board,m_position + shift) && legalMove(board,m_position,m_position+shift)) {
            m_possibleMoves.push_back(m_position + shift);
        }
    }
}