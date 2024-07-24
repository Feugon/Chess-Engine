#pragma once
#include <vector>

//TODO reconsider passing board as an arg


class basePiece {


public:
    basePiece(int position, bool is_white);


protected:

    bool m_isWhite;
    int m_position;

    std::vector<int> slidingMoves(const std::vector<int> &board, const std::vector<int> &shifts);
    bool isOccupiedByFriendly(const std::vector<int> &board, int  index);
    bool isOccupiedByEnemy(const std::vector<int> &board, int index);
    bool isSquareEmpty(const std::vector<int> &board, int index);
};