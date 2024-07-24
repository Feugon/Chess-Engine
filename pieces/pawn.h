#pragma once
#include <vector>
#include "basePiece.h"

class Pawn : public basePiece {
public:
    std::vector<int> pawnMoves(const std::vector<int> &board);
};

