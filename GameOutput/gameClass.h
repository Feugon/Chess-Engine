#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <memory>
#include <vector>
#include "../pieces/basePiece.h"


class chessGame {

public:
    chessGame(const std::string &FEN);
    void drawPosition(sf::RenderWindow &window);
    void drawPossibleMoves(sf::RenderWindow &window);
    void selectedSetter(int mouseX, int mouseY);
private:
    int m_selected;
    int m_lastSelected;
    int m_whiteKingPosition;
    int m_blackKingPosition;
    bool m_whiteToMove;
    std::vector<int> m_moveChoices;
    std::unordered_map<int,std::vector<int>> m_whiteMoves;
    std::unordered_map<int,std::vector<int>> m_blackMoves;
    std::vector<std::unique_ptr<basePiece>> m_board;

    void identifyMoves();
    void movePiece(int fromIndex, int toIndex);
    void castle(bool kingsideCastle);
};


/* Plan to find legal moves:
 * Keep track of kings positions                 |x|
 * Pass a board with the hypothetical move
 * check if king is in check
 * if it is then mark the move illegal
 * somehow remove the move from list of legal moves
 * animate the moves based on the whiteMoves hashmap or something
 */