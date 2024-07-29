#pragma once
#include "basePiece.h"
#include <vector>
#include <string>



class Bishop : public basePiece {
public:
    Bishop(int postion, bool is_white, std::string type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_bishop.png" : "../images/b_bishop.png";
    }


    std::vector<int> generateMoves(const std::vector<std::unique_ptr<basePiece>> &board) override;
};
