#pragma once
#include "basePiece.h"
#include <vector>
#include <string>



class Queen : public basePiece {
public:
    Queen(int postion, bool is_white, std::string type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_queen.png" : "../images/b_queen.png";
    }
    void generateMoves( std::vector<std::unique_ptr<basePiece>> &board) override;
};
