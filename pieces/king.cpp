#include "king.h"
#include "basePiece.h"
#include "rook.h"
#include <vector>
#include <iostream>


void King::canCastle(const std::vector <std::unique_ptr<basePiece>> &board) {

    inCheck(board);

    if(!m_hasMoved) {
        bool kingRookPresent = false;
        bool queenRookPresent = false;
        if(!isSquareEmpty(board,m_position+3)){kingRookPresent = board[m_position + 3]->getType() == "Rook";}
        if(!isSquareEmpty(board,m_position-4)){queenRookPresent = board[m_position - 4]->getType() == "Rook";}

        bool kingsRookMoved = true;
        bool queenRookMoved = true;

        if(kingRookPresent) {
            Rook* kingRook = dynamic_cast<Rook*>(board[m_position + 3].get());
            kingsRookMoved = kingRook->m_hasMoved;
        }
        if(queenRookPresent) {
            Rook* queenRook = dynamic_cast<Rook*>(board[m_position - 4].get());
            queenRookMoved = queenRook->m_hasMoved;
        }

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




void King::generateMoves(const std::vector<std::unique_ptr<basePiece>> &board) {

    m_possibleMoves.clear();
    // this corresponds to position shifts for a king
    int shifts[8] = {11,10,9,1,-1,-9,-10,-11};

    for(int shift : shifts) {
        if(!isOccupiedByFriendly(board,m_position + shift)) {
            m_possibleMoves.push_back(m_position + shift);
        }
    }

    canCastle(board);

   if (m_canKingsideCastle) {
       m_possibleMoves.push_back(m_position + 2);
   }
   if (m_canQueensideCastle) {
       m_possibleMoves.push_back(m_position - 2);
   }

}


bool King::inCheck(const std::vector<std::unique_ptr<basePiece> > &board) {
    if(m_isWhite) {
        //check if pawns are checking
        if(!isSquareEmpty(board, m_position - 9)) {
            if(board[m_position - 9]->getType() == "Pawn" && !(board[m_position - 9]->getIsWhite())) {
                return true;
            }
        } else if(!isSquareEmpty(board, m_position - 11)) {
            if(board[m_position - 11]->getType() == "Pawn" && !(board[m_position - 11]->getIsWhite())) {
                return true;
            }
        }
    } else {
        if(!isSquareEmpty(board, m_position + 9)) {
            if(board[m_position + 9]->getType() == "Pawn" && (board[m_position + 9]->getIsWhite())) {
                return true;
            }
        } else if(!isSquareEmpty(board, m_position + 11)) {
            if(board[m_position + 11]->getType() == "Pawn" && (board[m_position + 11]->getIsWhite())) {
                return true;
            }
        }
    }


    std::vector<int> upDownShifts = {10,1,-1,-10};;
    std::vector<int> upDownMoves = slidingMoves(board,upDownShifts);

    for(auto move : upDownMoves) {
        if(!isSquareEmpty(board, move)) {
            if((board[move]->getType() == "Rook" || board[move]->getType() == "Queen") && board[move]->getIsWhite() != m_isWhite) {
                return true;
            }
        }
    }

    std::vector<int> diagonalShifts = {11,9,-9,-11};
    std::vector<int> diagonalMoves = slidingMoves(board,diagonalShifts);
    for(auto move : diagonalMoves) {
        if(!isSquareEmpty(board, move)) {
            if((board[move]->getType() == "Bishop" || board[move]->getType() == "Queen") && board[move]->getIsWhite() != m_isWhite) {
                return true;
            }
        }
    }

    std::vector<int> knightShifts = {21,19,12,8,-21,-19,-12,-8};

    for(int shift : knightShifts) {
        if(!isSquareEmpty(board, m_position + shift)) {
            if(board[m_position + shift]->getType() == "Knight" && board[m_position + shift]->getIsWhite() != m_isWhite) {
                return true;
            }
        }
    }


    return false;
}








void King::setIndex(int index) {
    m_position = index;
    m_hasMoved = true;
    m_canKingsideCastle = false;
    m_canQueensideCastle = false;
}
