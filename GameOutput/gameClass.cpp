#include "gameClass.h"
#include <SFML/Graphics.hpp>
#include "../constants.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <cstdlib>

#include "../pieces/basePiece.h"
#include "../pieces/bishop.h"
#include "../pieces/knight.h"
#include "../pieces/pawn.h"
#include "../pieces/queen.h"
#include "../pieces/rook.h"
#include "../pieces/king.h"



// Returns a hashmap of index to smart pointer of the piece occupying the index
chessGame::chessGame(const std::vector<int> &board) {

    m_whiteMove = true;

    for (int i = 21; i < 99; i++) {

        bool is_white = board[i] > 0 ? true : false;
        int pieceVal = std::abs(board[i]);

        if (pieceVal == 1) {
            // Handle Pawn
            auto pawnPointer = std::make_unique<Pawn>(i, is_white);
            m_indexToPiece[i] = std::move(pawnPointer);
        } else if (pieceVal == 2) {
            // Handle Knight
            auto knightPointer = std::make_unique<Knight>(i, is_white);
            m_indexToPiece[i] = std::move(knightPointer);
        } else if (pieceVal == 3) {
            // Handle Bishop
            auto bishopPointer = std::make_unique<Bishop>(i, is_white);
            m_indexToPiece[i] = std::move(bishopPointer);
        } else if (pieceVal == 4) {
            // Handle Rook
            auto rookPointer = std::make_unique<Rook>(i, is_white);
            m_indexToPiece[i] = std::move(rookPointer);
        } else if (pieceVal == 5) {
            // Handle Queen
            auto queenPointer = std::make_unique<Queen>(i, is_white);
            m_indexToPiece[i] = std::move(queenPointer);
        } else if (pieceVal == 6) {
            // Handle King
            auto kingPointer = std::make_unique<King>(i, is_white);
            m_indexToPiece[i] = std::move(kingPointer);
        }

    }

}



void chessGame::drawPosition(sf::RenderWindow& window) {
    for(int i=0; i < 8; i++) {
        for(int j=0; j < 8; j++) {
            sf::Color color = (i+j)%2 == 0 ? constants::white : constants::black;
            sf::RectangleShape square(sf::Vector2f(constants::TILE_WIDTH, constants::TILE_HEIGHT));
            square.setFillColor(color);
            square.setPosition(constants::TILE_WIDTH * i, constants::TILE_HEIGHT * j);
            window.draw(square);
        }
    }

    // loops through all pointers and draws every piece
    for(auto& pair : m_indexToPiece) {
        pair.second->draw(window);
    }

}




void chessGame::drawPossibleMoves(sf::RenderWindow &window, const std::vector<int> &board) {


    int x = m_selected % 10 - 1;
    int y = (m_selected - 20) / 10;

    sf::RectangleShape square(sf::Vector2f(constants::TILE_WIDTH, constants::TILE_HEIGHT));
    square.setFillColor(constants::selected);
    square.setPosition(constants::TILE_WIDTH * x, constants::TILE_HEIGHT * y);
    window.draw(square);

    std::vector<int> moves;

    if(m_indexToPiece.count(m_selected) && m_indexToPiece[m_selected]) {
        moves = m_indexToPiece[m_selected]->generateMoves(board);
    }

    for(auto move: moves) {
        int x = move % 10 - 1;
        int y = (move - 20) / 10;

        sf::RectangleShape square(sf::Vector2f(constants::TILE_WIDTH, constants::TILE_HEIGHT));
        square.setFillColor(constants::selected);
        square.setPosition(constants::TILE_WIDTH * x, constants::TILE_HEIGHT * y);
        window.draw(square);
    }


}



void chessGame::selectedSetter(int mouseX, int mouseY) {
    int x = mouseX / constants::TILE_WIDTH;
    int y = mouseY / constants::TILE_HEIGHT;
    m_selected = 21 + (10*y) + x;

/*

    */
}

