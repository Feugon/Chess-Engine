#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <memory>

#include "../pieces/basePiece.h"

class chessGame {

public:
    chessGame(const std::vector<int> &board);
    void drawPosition(sf::RenderWindow &window);
    void drawPossibleMoves(sf::RenderWindow &window, const std::vector<int> &board);

    void selectedSetter(int mouseX, int mouseY);
private:
    int m_selected;
    bool m_whiteMove;
    std::unordered_map<int, std::unique_ptr<basePiece>> m_indexToPiece;
};
