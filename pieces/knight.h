#pragma once
#include <vector>
#include "basePiece.h"


class Knight : public basePiece {
    std::vector<int> knightMoves(const std::vector<int> &board);
};
