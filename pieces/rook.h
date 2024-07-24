#pragma once
#include "basePiece.h"
#include <vector>



class Rook : public basePiece {
public:
    std::vector<int> rookMoves(const std::vector<int> &board);
};
