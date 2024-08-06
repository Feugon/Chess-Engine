#pragma once
#include <vector>
#include "basePiece.h"
#include <string>
#include <iostream>
#include "rook.h"



class King : public basePiece {
public:
    King(int postion, bool is_white, PieceType type): basePiece(postion, is_white, type) {
        m_imageDir = is_white ? "../images/w_king.png" : "../images/b_king.png";
        basePiece::m_whiteKingPosition = is_white ? m_position : m_whiteKingPosition;
        basePiece::m_blackKingPosition = is_white ? m_blackKingPosition : m_position;
    }
    void generateMoves(std::vector<std::unique_ptr<basePiece>> &board) override;
    void move(int index) override;
    void setIndex(int index) override {m_position = index;}
    void canCastle(std::vector<std::unique_ptr<basePiece>> &board);
    bool inCheck( std::vector<std::unique_ptr<basePiece>> &board) override;

private:
    bool m_hasMoved = false;
    bool m_canKingsideCastle = false;
    bool m_canQueensideCastle = false;
};

