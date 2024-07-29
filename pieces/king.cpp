#include "king.h"
#include "basePiece.h"
#include "rook.h"
#include <vector>
#include <unordered_map>
#include <iostream>


void King::canCastle(std::unordered_map<int, std::unique_ptr<basePiece>> &pointerMap, const std::vector<int> &board) {

    bool kingRookPresent = board[m_position + 3] == 4 || board[m_position + 3] == - 4;
    bool queenRookPresent = board[m_position - 4] == 4 || board[m_position - 4] == -4;
    bool kingsRookMoved;
    bool queenRookMoved;

    if(kingRookPresent) {
        Rook* kingRook = dynamic_cast<Rook*>(pointerMap[m_position + 3].get());
        kingsRookMoved = kingRook->m_hasMoved;

    }
    if(queenRookPresent) {
        Rook* queenRook = dynamic_cast<Rook*>(pointerMap[m_position - 4].get());
        queenRookMoved = queenRook->m_hasMoved;
        std::cout << queenRookMoved;
    }

    if(!m_hasMoved) {
        bool kingsideEmpty = isSquareEmpty(board,m_position + 1) && isSquareEmpty(board,m_position + 2);
        bool queensideEmpty = isSquareEmpty(board,m_position - 1) && isSquareEmpty(board,m_position - 2) && isSquareEmpty(board,m_position - 3);
        if(!kingsRookMoved && kingsideEmpty) {
            m_canKingsideCastle = true;
        }
        if(!queenRookMoved && queensideEmpty) {
            m_canQueensideCastle = true;
        }
    }
}




std::vector<int> King::generateMoves(const std::vector<int> &board) {

    std::vector<int> possibleMoves;

    // this corresponds to position shifts for a king
    int shifts[8] = {11,10,9,1,-1,-9,-10,-11};

    for(int shift : shifts) {
        if(!isOccupiedByFriendly(board,m_position + shift)) {
            possibleMoves.push_back(m_position + shift);
        }
    }

   if (m_canKingsideCastle) {
       possibleMoves.push_back(m_position + 2);
   }
   if (m_canQueensideCastle) {
       possibleMoves.push_back(m_position - 2);
   }

    return possibleMoves;
}


void King::setIndex(int index) {
    m_position = index;
    m_hasMoved = true;

    if(m_position - index == -2 || m_position - index == 2) {

    }
}
