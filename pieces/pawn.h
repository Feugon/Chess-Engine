#pragma once
#include <vector>
#include "basePiece.h"
#include <string>
#include <iostream>



class Pawn : public basePiece {
public:
    Pawn(int postion, bool is_white, PieceType type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_pawn.png" : "../images/b_pawn.png";
        m_value = 100;
        m_positionBonus = m_positionBonus = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0,  0,  0,  0,  0,  0,  0,  0, 0,
            0, 50, 50, 50, 50, 50, 50, 50, 50, 0,
            0, 10, 10, 20, 30, 30, 20, 10, 10, 0,
            0,  5,  5, 10, 25, 25, 10,  5,  5, 0,
            0,  0,  0,  0, 20, 20,  0,  0,  0, 0,
            0,  5, -5,-10,  0,  0,-10, -5,  5, 0,
            0, 5, 10, 10,-20,-20, 10, 10,  5, 0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };
    }
    void generateMoves(std::vector<std::unique_ptr<basePiece>> &board) override;
    void move(int index) override;

};

