#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stack>
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
    void makeMove(Move move);
    void unmakeMove(Move move);
    std::vector<Move> getMoves(int depth = 1);
private:
    bool m_checkmate = false;
    int m_selected;
    int m_lastSelected;
    int m_whiteKingPosition;
    int m_blackKingPosition;
    bool m_whiteToMove;
    bool m_lastMoveWasPromotion;
    std::vector<int> m_moveChoices;
    std::vector<Move> m_whiteMoves;
    std::vector<Move>  m_blackMoves;
    std::vector<std::unique_ptr<basePiece>> m_board;
    std::stack<std::unique_ptr<basePiece>> m_lastOccupied;
    std::unique_ptr<basePiece> m_enPassantedPawn;



    void identifyMoves();
    void castle(bool kingsideCastle);
};


