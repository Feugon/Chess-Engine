#pragma once
#include "basePiece.h"
#include <vector>



class Bishop : public basePiece {
public:
    std::vector<int> bishopMoves(const std::vector<int> &board);
};
