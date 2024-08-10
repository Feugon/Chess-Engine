#pragma once
#include "basePiece.h"
#include <vector>
#include <string>



class Bishop : public basePiece {
public:
    Bishop(int postion, bool is_white, PieceType type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_bishop.png" : "../images/b_bishop.png";
        m_value = 330;
        m_positionBonus = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, -20, -10, -10, -10, -10, -10, -10, -20, 0,
            0, -10,  0,   0,   0,   0,   0, 0, -10, 0,
            0, -10,  0,  5, 10, 10,  5,  0, -10, 0,
            0, -10,  5,  5, 10, 10,  5,  5, -10, 0,
            0, -10,  0, 10, 10, 10, 10,  0, -10, 0,
            0, -10, 10, 10, 10, 10, 10, 10, -10, 0,
            0, -10,  5,  0,  0,  0,  0,  5, -10, 0,
            0, -20, -10, -10, -10, -10, -10, -10, -20, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };

    }
    void generateMoves(std::vector<std::unique_ptr<basePiece>> &board) override;
};
