#include "king.h"
#include "basePiece.h"
#include "rook.h"
#include <vector>
#include <iostream>


void King::canCastle(std::vector <std::unique_ptr<basePiece>> &board) {

    m_canKingsideCastle = false;
    m_canQueensideCastle = false;

    if(!m_hasMoved && !(this->inCheck(board))) {
        bool kingRookPresent = false;
        bool queenRookPresent = false;
        if(!isSquareEmpty(board,m_position+3)){kingRookPresent = board[m_position + 3]->getType() == rook;}
        if(!isSquareEmpty(board,m_position-4)){queenRookPresent = board[m_position - 4]->getType() == rook;}

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

        // legal move part checks if the rook would be under attack by pretending its a king
        if(!kingsRookMoved && kingsideEmpty && legalMove(board,m_position,m_position+1)) {
            m_canKingsideCastle = true;
        }
        if(!queenRookMoved && queensideEmpty && legalMove(board,m_position,m_position-1)) {
            m_canQueensideCastle = true;
        }
    }

}




void King::generateMoves(std::vector<std::unique_ptr<basePiece>> &board) {

    m_possibleMoves.clear();
    std::vector<int> potentialMoves;
    // this corresponds to position shifts for a king
    int shifts[8] = {11,10,9,1,-1,-9,-10,-11};


    for(int shift : shifts) {
        if(!isOccupiedByFriendly(board,m_position + shift)) {
            potentialMoves.push_back(m_position + shift);
        }
    }

    canCastle(board);
   if (m_canKingsideCastle) {
       potentialMoves.push_back(m_position + 2);
   }
   if (m_canQueensideCastle) {
       potentialMoves.push_back(m_position - 2);
   }

    for(int move: potentialMoves) {
        if(legalMove(board, m_position, move)) {
            m_possibleMoves.push_back(move);
        }
    }

}


bool King::inCheck(std::vector<std::unique_ptr<basePiece>> &board) {
    if(m_isWhite) {
        //check if pawns are checking
        if(!isSquareEmpty(board, m_position - 9)) {
            if(board[m_position - 9]->getType() == pawn && !(board[m_position - 9]->getIsWhite())) {
                return true;
            }
        }
        if(!isSquareEmpty(board, m_position - 11)) {
            if(board[m_position - 11]->getType() == pawn && !(board[m_position - 11]->getIsWhite())) {
                return true;
            }
        }
    } else {
        if(!isSquareEmpty(board, m_position + 9)) {
            if(board[m_position + 9]->getType() == pawn && (board[m_position + 9]->getIsWhite())) {
                return true;
            }
        }
        if(!isSquareEmpty(board, m_position + 11)) {
            if(board[m_position + 11]->getType() == pawn && (board[m_position + 11]->getIsWhite())) {
                return true;
            }
        }
    }


    std::vector<int> upDownShifts = {10,1,-1,-10};;
    std::vector<int> upDownMoves = slidingMoves(board,upDownShifts);

    for(auto move : upDownMoves) {
        if(!isSquareEmpty(board, move)) {
            if((board[move]->getType() == rook || board[move]->getType() == queen) && board[move]->getIsWhite() != m_isWhite) {
                return true;
            }
        }
    }

    std::vector<int> diagonalShifts = {11,9,-9,-11};
    std::vector<int> diagonalMoves = slidingMoves(board,diagonalShifts);
    for(auto move : diagonalMoves) {
        if(!isSquareEmpty(board, move)) {
            if((board[move]->getType() == bishop || board[move]->getType() == queen) && board[move]->getIsWhite() != m_isWhite) {
                return true;
            }
        }
    }

    std::vector<int> knightShifts = {21,19,12,8,-21,-19,-12,-8};

    for(int shift : knightShifts) {
        if(!isSquareEmpty(board, m_position + shift)) {
            if(board[m_position + shift]->getType() == knight && board[m_position + shift]->getIsWhite() != m_isWhite) {
                return true;
            }
        }
    }


    return false;
}








void King::move(int index) {
    m_position = index;
    m_hasMoved = true;
    m_canKingsideCastle = false;
    m_canQueensideCastle = false;

    if(m_isWhite) {
        basePiece::m_whiteKingPosition = index;
    } else {
        basePiece::m_blackKingPosition = index;
    }
}
