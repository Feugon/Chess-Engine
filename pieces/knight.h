#pragma once
#include <vector>
#include "basePiece.h"
#include <string>

class Knight : public basePiece {
public:
    Knight(int postion, bool is_white, PieceType type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_knight.png" : "../images/b_knight.png";
    }
    void generateMoves( std::vector<std::unique_ptr<basePiece>> &board) override;
};
