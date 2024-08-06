#pragma once
#include <vector>
#include "basePiece.h"
#include <string>

class Padding : public basePiece {
public:
    Padding(int postion,bool is_white, PieceType type): basePiece(postion, is_white, type){}

    void generateMoves(std::vector<std::unique_ptr<basePiece>> &board) override {}
};
