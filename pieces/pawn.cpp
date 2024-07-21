#include "pawn.h"
#include "pieceMovement.h"
#include <vector>

// This whole thing should probably be cleaned up (for now it works as intended though
// TODO add promotion here

std::vector<int> pawnMoves(int index, const std::vector<int> &board) {

    std::vector<int> possibleMoves;
    bool isWhitePawn = board[index] > 0;

    // if on the 2nd/7th rank and appropriate color then pawn can move twice
    bool moveTwo = (index / 10 == 3 && !isWhitePawn) || (index / 10 == 8 && isWhitePawn);

    // a lot of magic numbers, these all just correspond to index change of a pawn move
    if(isWhitePawn) {
        if(isSquareEmpty(board,index-10)) {possibleMoves.push_back(index - 10);}
        if(isSquareEmpty(board,index-20) && moveTwo){possibleMoves.push_back(index - 20);}
        if(isOccupiedByEnemy(board, index - 11, isWhitePawn)){possibleMoves.push_back(index - 11);}
        if(isOccupiedByEnemy(board, index - 9, isWhitePawn)){possibleMoves.push_back(index - 9);}
    } else {
        if(isSquareEmpty(board,index+10)) {possibleMoves.push_back(index + 10);}
        if(isSquareEmpty(board,index+20) && moveTwo){possibleMoves.push_back(index + 20);}
        if(isOccupiedByEnemy(board, index + 11, !isWhitePawn)){possibleMoves.push_back(index + 11);}
        if(isOccupiedByEnemy(board, index + 9, !isWhitePawn)){possibleMoves.push_back(index + 9);}
    }

    return possibleMoves;
}