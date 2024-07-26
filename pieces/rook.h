#pragma once
#include "basePiece.h"
#include <vector>
#include <string>


class Rook : public basePiece {
public:
    Rook(int postion, bool is_white): basePiece(postion, is_white) {
        m_imageDir = is_white ? "../images/w_rook.png" : "../images/b_rook.png";
    }
    std::vector<int> generateMoves(const std::vector<int> &board) override;
};
