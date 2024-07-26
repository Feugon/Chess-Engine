#pragma once
#include "basePiece.h"
#include <vector>
#include <string>



class Bishop : public basePiece {
public:
    Bishop(int postion, bool is_white): basePiece(postion, is_white) {
        m_imageDir = is_white ? "../images/w_bishop.png" : "../images/b_bishop.png";
    }
    std::vector<int> generateMoves(const std::vector<int> &board) override;
};
