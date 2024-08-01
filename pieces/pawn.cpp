#include "pawn.h"
#include "basePiece.h"
#include <vector>

// TODO add promotion

void Pawn::generateMoves(std::vector<std::unique_ptr<basePiece>> &board) {

    m_possibleMoves.clear();
    std::vector<int> potentialMoves;

    // if on the 2nd/7th rank and appropriate color then pawn can move twice
    bool moveTwo = (m_position / 10 == 3 && !m_isWhite) || (m_position / 10 == 8 && m_isWhite);

    // a lot of magic numbers, these all just correspond to index change of a pawn move
    if(m_isWhite) {
        if(isSquareEmpty(board,m_position-10)) {potentialMoves.push_back(m_position - 10);}
        if(isSquareEmpty(board,m_position-20) && moveTwo && isSquareEmpty(board,m_position-10)) {
            potentialMoves.push_back(m_position - 20);
        }
        if(isOccupiedByEnemy(board, m_position - 11)){potentialMoves.push_back(m_position - 11);}
        if(isOccupiedByEnemy(board, m_position - 9)){potentialMoves.push_back(m_position - 9);}
    } else {
        if(isSquareEmpty(board,m_position + 10)) {potentialMoves.push_back(m_position + 10);}
        if(isSquareEmpty(board,m_position + 20) && moveTwo && isSquareEmpty(board,m_position + 10)) {
            potentialMoves.push_back(m_position + 20);
        }
        if(isOccupiedByEnemy(board, m_position + 11)){potentialMoves.push_back(m_position + 11);}
        if(isOccupiedByEnemy(board, m_position + 9)){potentialMoves.push_back(m_position + 9);}
    }

    // this should be its own function at this point....
    for(int move: potentialMoves) {
        if(legalMove(board, m_position, move)) {
            m_possibleMoves.push_back(move);
        }
    }

}