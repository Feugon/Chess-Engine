#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class chessGame {

public:
    void drawBoard(sf::RenderWindow &window);
    void drawSelected(sf::RenderWindow &window);
    void drawPieces(sf::RenderWindow &window, const std::vector<int> &board);
    void selectedSetter(int mouseX, int mouseY);
private:
    int m_selected;
};