#pragma once
#include <vector>
#include "basePiece.h"
#include <string>

class Padding : public basePiece {
public:
    Padding(int postion,bool is_white, std::string type): basePiece(postion, is_white, type){}

    std::vector<int> generateMoves(const std::vector<std::unique_ptr<basePiece>> &board) override {
        return {};
    }
};
