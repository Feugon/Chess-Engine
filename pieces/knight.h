#pragma once
#include <vector>
#include "basePiece.h"
#include <string>

class Knight : public basePiece {
public:
    Knight(int postion, bool is_white, PieceType type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_knight.png" : "../images/b_knight.png";
        m_value = 320;
        m_positionBonus = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, -50,-40,-30,-30,-30,-30,-40,-50, 0,
            0, -40,-20,  0,  0,  0,  0,-20,-40, 0,
            0, -30,  0, 10, 15, 15, 10,  0,-30, 0,
            0, -30,  5, 15, 20, 20, 15,  5,-30, 0,
            0, -30,  0, 15, 20, 20, 15,  0,-30, 0,
            0, -30,  5, 10, 15, 15, 10,  5,-30, 0,
            0, -40,-20,  0,  5,  5,  0,-20,-40, 0,
            0, -50,-40,-30,-30,-30,-30,-40,-50, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        };
    }
    void generateMoves( std::vector<std::unique_ptr<basePiece>> &board) override;
};
