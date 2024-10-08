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
        m_value = 0;
        m_positionBonus = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, -10,  -10,  -15,  -20,  -20,  -15,  -10, -10, 0,
            0, -10,  -10,  -15,  -20,  -20,  -15,  -10, -10, 0,
            0, -10,  -10,  -15,  -20,  -20,  -15,  -10, -10, 0,
            0, -15,  -15,  -20,  -25,  -25,  -20,  -15, -15, 0,
            0, -15,  -15,  -20,  -25,  -25,  -20,  -15, -15, 0,
            0, -10,  -10,  -15,  -20,  -20,  -15,  -10, -10, 0,
            0, -5,  -5,  -5,  -10,  -10,  -5,  -5, -5, 0,
            0, 5, 20, 15, -5, 0, -5, 20, 15, 5,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };
    }
    void generateMoves(std::vector<std::unique_ptr<basePiece>> &board) override;
    void move(int index) override;
    void setIndex(int index) override {m_position = index;}
    void canCastle(std::vector<std::unique_ptr<basePiece>> &board);
    bool inCheck(std::vector<std::unique_ptr<basePiece>> &board) override;
    int m_timesMoved = 0; // this probably should be in private and should make some setter method...

private:
    bool m_canKingsideCastle = false;
    bool m_canQueensideCastle = false;
};

