#pragma once
#include <vector>
#include "basePiece.h"
#include <string>
#include <iostream>

class King : public basePiece {
public:
    King(int postion, bool is_white): basePiece(postion, is_white) {
        m_imageDir = is_white ? "../images/w_king.png" : "../images/b_king.png";
    }
    std::vector<int> generateMoves(const std::vector<int> &board) override;
};

