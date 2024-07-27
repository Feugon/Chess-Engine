#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <memory>
#include <vector>
#include "../pieces/basePiece.h"


class chessGame {

public:
    chessGame(const std::vector<int> &board);
    void drawPosition(sf::RenderWindow &window);
    void drawPossibleMoves(sf::RenderWindow &window, const std::vector<int> &board);
    void selectedSetter(int mouseX, int mouseY, std::vector<int> &board);
private:
    int m_selected;
    int m_lastSelected;
    bool m_whiteMove;
    std::vector<int> m_availableMoves;
    std::unordered_map<int, std::unique_ptr<basePiece>> m_indexToPiece;
    void movePiece(int fromIndex, int toIndex, std::vector<int> &board);
};
