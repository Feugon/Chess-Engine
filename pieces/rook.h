#pragma once
#include "basePiece.h"
#include <vector>
#include <string>


class Rook : public basePiece {
public:
    Rook(int postion, bool is_white, PieceType type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_rook.png" : "../images/b_rook.png";
    }
    void generateMoves(std::vector<std::unique_ptr<basePiece>> &board) override;
    void move(int index) override;

    int m_timesMoved = 0;

    friend class King;
};
