#include "knight.h"
#include "pieceMovement.h"
#include <vector>

std::vector<int> knightMoves(int index, const std::vector<int> &board) {

    std::vector<int> possibleMoves;
    bool isWhite = board[index] > 0;

    // this corresponds to position shifts for a knight
    int shifts[8] = {21,19,12,8,-21,-19,-12,-8};


    for(int shift : shifts) {
        if(!isOccupiedByFriendly(board,index + shift,isWhite)) {
            possibleMoves.push_back(index + shift);
        }
    }



    return possibleMoves;
}