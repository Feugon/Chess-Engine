#pragma once
#include <vector>
#include "basePiece.h"
#include <string>

class Knight : public basePiece {
public:
    Knight(int postion, bool is_white, std::string type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_knight.png" : "../images/b_knight.png";
    }
    std::vector<int> generateMoves(const std::vector<int> &board) override;
};
