#pragma once
#include "basePiece.h"
#include <vector>



class Queen : public basePiece {
public:
    std::vector<int> queenMoves(const std::vector<int> &board);
};
