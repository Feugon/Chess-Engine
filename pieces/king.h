#pragma once
#include <vector>
#include "basePiece.h"
#include <string>
#include <iostream>
#include "rook.h"



class King : public basePiece {
public:
    King(int postion, bool is_white, std::string type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_king.png" : "../images/b_king.png";
    }
    void generateMoves(const std::vector<std::unique_ptr<basePiece>> &board) override;
    void setIndex(int index) override;
    void canCastle(const std::vector<std::unique_ptr<basePiece>> &board);
    bool inCheck(const std::vector<std::unique_ptr<basePiece>> &board);

private:
    bool m_hasMoved = false;
    bool m_canKingsideCastle = false;
    bool m_canQueensideCastle = false;
};

