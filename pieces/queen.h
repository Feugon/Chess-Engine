#pragma once
#include "basePiece.h"
#include <vector>
#include <string>



class Queen : public basePiece {
public:
    Queen(int postion, bool is_white): basePiece(postion, is_white) {
        m_imageDir = is_white ? "../images/w_queen.png" : "../images/b_queen.png";
    }
    std::vector<int> generateMoves(const std::vector<int> &board) override;
};
