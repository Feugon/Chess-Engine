#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include <stack>
#include "pieces/basePiece.h"


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
    void makeMove(Move move, int depth = 1);
    void unmakeMove(Move move);
    std::vector<Move> getMoves();
    std::vector<std::unique_ptr<basePiece>> m_board;
    void identifyMoves();
    bool getGameOver(){return m_checkmate || m_stalemate;}
    bool getWhiteToMove(){return m_whiteToMove;}
    Move m_lastMove;
private:
    bool m_checkmate = false;
    bool m_stalemate = false;
    int m_selected;
    int m_lastSelected;
    int m_whiteKingPosition;
    int m_blackKingPosition;
    bool m_whiteToMove;
    bool m_lastMoveWasPromotion;
    std::vector<int> m_moveChoices;
    std::vector<Move> m_whiteMoves;
    std::vector<Move>  m_blackMoves;
    std::stack<std::unique_ptr<basePiece>> m_lastOccupied;
    std::unique_ptr<basePiece> m_enPassantedPawn;


    void castle(bool kingsideCastle);
};


