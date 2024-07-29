#include "knight.h"
#include "basePiece.h"
#include <vector>
#include <iostream>


std::vector<int> Knight::generateMoves(const std::vector<std::unique_ptr<basePiece>> &board) {

    std::vector<int> possibleMoves;

    // this corresponds to position shifts for a knight
    int shifts[8] = {21,19,12,8,-21,-19,-12,-8};

    for(int shift : shifts) {
        if(!isOccupiedByFriendly(board,m_position + shift)) {
            possibleMoves.push_back(m_position + shift);
        }
    }

    return possibleMoves;
}