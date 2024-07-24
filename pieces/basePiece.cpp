#include "basePiece.h"



basePiece::basePiece(int position, bool is_white) {
    m_position = position;
    m_isWhite = is_white;
}



bool basePiece::isOccupiedByFriendly(const std::vector<int> &board, int index) {
    bool occupiedByFriend;

    if(m_isWhite) {
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


bool basePiece::isSquareEmpty(const std::vector<int> &board, int index) {
    bool empty = board[index] == 0 ? true : false;
    return empty;
}

bool basePiece::isOccupiedByEnemy(const std::vector<int> &board, int index) {
    bool occupiedByEnemy;

    if(m_isWhite) {
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



std::vector<int> basePiece::slidingMoves(const std::vector<int> &board, const std::vector<int> &shifts) {

    std::vector<int> possibleMoves;

    for(int shift: shifts) {
        int distance = 1;
        while(board[m_position + distance * shift] != 7) {
            if(isOccupiedByFriendly(board,m_position + distance * shift)) {
                break;
            } else if(isOccupiedByEnemy(board, m_position + distance * shift)) {
                possibleMoves.push_back(m_position + distance * shift);
                break;
            } else {
                possibleMoves.push_back(m_position + distance * shift);
                distance++;
            }
        }
    }

    return possibleMoves;
}