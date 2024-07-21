#include "pieceMovement.h"

//TODO add out of bounds behavior here

bool isOccupiedByFriendly(const std::vector<int> &board, int index, bool isWhite) {
    bool occupiedByFriend;

    if(isWhite) {
        if(board[index] > 0 && board[index] != 7) {
            occupiedByFriend = true;
        } else {
            occupiedByFriend = false;
        }
    } else {
        if(board[index] < 0) {
            occupiedByFriend = true;
        } else {
            occupiedByFriend = false;
        }
    }

    return occupiedByFriend;
}


bool isSquareEmpty(const std::vector<int> &board, int index ) {
    bool empty = board[index] == 0 ? true : false;
    return empty;
}

bool isOccupiedByEnemy(const std::vector<int> &board, int index, bool isWhite) {
    bool occupiedByEnemy;

    if(isWhite) {
        if(board[index] < 0) {
            occupiedByEnemy = true;
        } else {
            occupiedByEnemy = false;
        }
    } else {
        if(board[index] > 0 && board[index] != 7) {
            occupiedByEnemy = true;
        } else {
            occupiedByEnemy = false;
        }
    }

    return occupiedByEnemy;
}



std::vector<int> slidingMoves(const std::vector<int> &board, int index, bool isWhite, const std::vector<int> &shifts) {

    std::vector<int> possibleMoves;

    for(int shift: shifts) {
        int distance = 1;
        while(board[index + distance * shift] != 7) {
            if(isOccupiedByFriendly(board,index + distance * shift, isWhite)) {
                break;
            } else if(isOccupiedByEnemy(board,index + distance * shift, isWhite)) {
                possibleMoves.push_back(index + distance * shift);
                break;
            } else {
                possibleMoves.push_back(index + distance * shift);
                distance++;
            }
        }
    }

    return possibleMoves;
}