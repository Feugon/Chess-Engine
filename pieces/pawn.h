#pragma once
#include <vector>
#include "basePiece.h"
#include <string>
#include <iostream>



class Pawn : public basePiece {
public:
    Pawn(int postion, bool is_white, std::string type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_pawn.png" : "../images/b_pawn.png";
    }
    void generateMoves(std::vector<std::unique_ptr<basePiece>> &board) override;
    void move(int index) override;

};

