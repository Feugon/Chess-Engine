#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <memory>
#include "../pieces/basePiece.h"

struct Move {
    int from;
    int to;
};

class chessGame {

public:
    chessGame(const std::string &FEN);
    void drawPosition(sf::RenderWindow &window);
    void drawPossibleMoves(sf::RenderWindow &window);
    void selectedSetter(int mouseX, int mouseY);
    std::vector<Move> getMoves();
private:
    int m_selected;
    int m_lastSelected;
    int m_whiteKingPosition;
    int m_blackKingPosition;
    bool m_whiteToMove;
    std::vector<int> m_moveChoices;
    std::vector<Move> m_whiteMoves;
    std::vector<Move>  m_blackMoves;
    std::vector<std::unique_ptr<basePiece>> m_board;

    void identifyMoves();
    void makeMove(Move move);
    void unmakeMove(Move move);
    void castle(bool kingsideCastle);
};


