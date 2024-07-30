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
    bool m_whiteMove;
    std::vector<int> m_availableMoves;
    std::vector<std::unique_ptr<basePiece>> m_board;
    void movePiece(int fromIndex, int toIndex);
    void castle(bool kingsideCastle);
};
