#pragma once
#include "basePiece.h"
#include <vector>
#include <string>


class Rook : public basePiece {
public:
    Rook(int postion, bool is_white, std::string type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_rook.png" : "../images/b_rook.png";
    }
    void generateMoves(const std::vector<std::unique_ptr<basePiece>> &board) override;
    void setIndex(int index) override;

    friend class King;
private:
    bool m_hasMoved = false;
};
