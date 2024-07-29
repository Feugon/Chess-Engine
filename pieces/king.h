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
    std::vector<int> generateMoves(const std::vector<int> &board) override;
    void setIndex(int index) override;
    void canCastle(std::unordered_map<int, std::unique_ptr<basePiece>> &pointerMap, const std::vector<int> &board);


private:
    bool m_hasMoved = false;
    bool m_canKingsideCastle = false;
    bool m_canQueensideCastle = false;
};

