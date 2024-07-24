#include "gameClass.h"
#include <SFML/Graphics.hpp>
#include "constants.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include <cstdlib>


void chessGame::drawBoard(sf::RenderWindow& window) {
    for(int i=0; i < 8; i++) {
        for(int j=0; j < 8; j++) {
            sf::Color color = (i+j)%2 == 0 ? constants::white : constants::black;
            sf::RectangleShape square(sf::Vector2f(constants::TILE_WIDTH, constants::TILE_HEIGHT));
            square.setFillColor(color);
            square.setPosition(constants::TILE_WIDTH * i, constants::TILE_HEIGHT * j);
            window.draw(square);
        }
    }
}


void chessGame:: drawSelected(sf::RenderWindow &window) {
    int x = m_selected % 10 - 1;
    int y = (m_selected - 20) / 10;
    sf::RectangleShape square(sf::Vector2f(constants::TILE_WIDTH, constants::TILE_HEIGHT));
    square.setFillColor(constants::selected);
    square.setPosition(constants::TILE_WIDTH * x, constants::TILE_HEIGHT * y);
    window.draw(square);
}


void chessGame::drawPieces(sf::RenderWindow &window, const std::vector<int> &board) {

    std::unordered_map<int, std::string> intToPiece = {
    {1, "pawn"}, {2,"knight"}, {3,"bishop"},
    {4, "rook"}, {5,"queen"}, {6,"king"}};

    for (int i = 21; i < 99; i++) {
        if(board[i] == 7 || board[i] == 0) {
            continue;
        } else {
            std::string prefix = board[i] > 0 ? "w_" : "b_";
            std::string pieceName = intToPiece[abs(board[i])];
            std::string fileName = "../images/" + prefix + pieceName + ".png";

            sf::Texture texture;
            texture.loadFromFile(fileName);
            sf::Sprite sprite;
            sprite.setTexture(texture);

            int y_cord = i / 10 - 2;
            int x_cord = i % 10 - 1;


            // TODO figure out the equation for the buffer here...
            sprite.setPosition(x_cord * constants::TILE_WIDTH + 2, y_cord * constants::TILE_HEIGHT + 2);
            sprite.scale(1.2, 1.2);
            window.draw(sprite);
        }
    }
}




void chessGame::selectedSetter(int mouseX, int mouseY) {
    int x = mouseX / constants::TILE_WIDTH;
    int y = mouseY / constants::TILE_HEIGHT;
    m_selected = 21 + (10*y) + x;
}

