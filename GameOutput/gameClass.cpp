#include "gameClass.h"
#include <SFML/Graphics.hpp>
#include "../constants.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <cctype>
#include <cstdlib>

#include "../pieces/basePiece.h"
#include "../pieces/bishop.h"
#include "../pieces/knight.h"
#include "../pieces/pawn.h"
#include "../pieces/queen.h"
#include "../pieces/rook.h"
#include "../pieces/king.h"
#include "../pieces/padding.h"


// Creates a vector of pointers of the pieces based on the FEN string
chessGame::chessGame(const std::string &FEN) {

    m_whiteToMove = true;
    int stringIndex = 0;

    for (int i=0; i<120; i++) {
        if(i < 21 || i > 98 || i % 10 == 0 || i % 10 == 9) {
            auto paddingPointer = std::make_unique<Padding>(i, false, "Padding");
            m_board.push_back(std::move(paddingPointer));

        } else if (std::isdigit(FEN[stringIndex])) {
            // empty spaces... not super readable code
            int numSpaces = FEN[stringIndex] - '0';
            stringIndex++;
            for(int j = 0; j < numSpaces; j++) {
                m_board.push_back(nullptr);
            }
            i += numSpaces - 1;

            //idk if this should be here
            if(FEN[stringIndex] == '/') {
                stringIndex++;
            }


        } else if (FEN[stringIndex] != '/'){
            //The above condition check seems dumb... will deal with it later
            bool is_white = std::isupper(FEN[stringIndex]);

            if (FEN[stringIndex] == 'p' || FEN[stringIndex] == 'P') {
                // Handle Pawn
                auto pawnPointer = std::make_unique<Pawn>(i, is_white, "Pawn");
                m_board.push_back(std::move(pawnPointer));
            } else if (FEN[stringIndex] == 'n' || FEN[stringIndex] == 'N') {
                // Handle Knight
                auto knightPointer = std::make_unique<Knight>(i, is_white, "Knight");
                m_board.push_back(std::move(knightPointer));
            } else if (FEN[stringIndex] == 'b' || FEN[stringIndex] == 'B') {
                // Handle Bishop
                auto bishopPointer = std::make_unique<Bishop>(i, is_white, "Bishop");
                m_board.push_back(std::move(bishopPointer));
            } else if (FEN[stringIndex] == 'r' || FEN[stringIndex] == 'R') {
                // Handle Rook
                auto rookPointer = std::make_unique<Rook>(i, is_white, "Rook");
                m_board.push_back(std::move(rookPointer));
            } else if (FEN[stringIndex] == 'q' || FEN[stringIndex] == 'Q') {
                // Handle Queen
                auto queenPointer = std::make_unique<Queen>(i, is_white,"Queen");
                m_board.push_back(std::move(queenPointer));
            } else if (FEN[stringIndex] == 'k' || FEN[stringIndex] == 'K') {
                // Handle King
                auto kingPointer = std::make_unique<King>(i, is_white, "King");
                m_board.push_back(std::move(kingPointer));

                if(is_white) {
                    m_whiteKingPosition = i;
                } else {
                    m_blackKingPosition = i;
                }
            }

            stringIndex++;
            if(FEN[stringIndex] == '/') {
                stringIndex++;
            }

        }
    }
    identifyMoves();
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
    for(auto& pointer : m_board) {
        if(pointer && pointer->getType() != "Padding") {
            pointer->draw(window);
        }
    }

}



void chessGame::drawPossibleMoves(sf::RenderWindow &window) {

    int selectedX = m_selected % 10 - 1;
    int selectedY = (m_selected - 20) / 10;

    std::vector<int> moves;
    moves.push_back(m_selected);
    moves.insert(moves.end(), m_moveChoices.begin(), m_moveChoices.end());


    // Draw the initial square and all generated move squares
    for (auto move : moves) {
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


    // checks if we are moving the piece
    bool selectedMove = std::find(m_moveChoices.begin(), m_moveChoices.end(), m_selected) != m_moveChoices.end();
    if (selectedMove) {
        movePiece(m_lastSelected,m_selected);
    }

    m_moveChoices.clear();

    // if we select the right colored piece then gets its possible moves
    if(m_board[m_selected]) {
        if((m_board[m_selected]->getIsWhite() && m_whiteToMove)) {
            m_moveChoices = m_whiteMoves[m_selected];
        } else if ( (!m_board[m_selected]->getIsWhite() && !m_whiteToMove)) {
            m_moveChoices = m_blackMoves[m_selected];
        }
    }

    m_lastSelected = m_selected;
}


void chessGame::castle(bool kingsideCastle) {
    if(kingsideCastle) {
        m_board[m_lastSelected + 3]->setIndex(m_lastSelected + 1);
        m_board[m_lastSelected + 1] = std::move(m_board[m_lastSelected + 3]);
        m_board[m_lastSelected + 3] = nullptr;
    } else {
        m_board[m_lastSelected - 4]->setIndex(m_lastSelected - 1);
        m_board[m_lastSelected - 1] = std::move(m_board[m_lastSelected - 4]);
        m_board[m_lastSelected - 4] = nullptr;
    }
}


void chessGame::identifyMoves() {

    m_whiteMoves.clear();
    m_blackMoves.clear();

    for (auto& piece : m_board) {
        if(piece != nullptr){
            if(piece->getType() != "Padding" && piece->getIsWhite() && m_whiteToMove) {
                piece->generateMoves(m_board);
                m_whiteMoves[piece->getPosition()] = piece->getMoves();
            } else if (piece->getType() != "Padding" && !piece->getIsWhite() && !m_whiteToMove) {
                piece->generateMoves(m_board);
                m_blackMoves[piece->getPosition()] = piece->getMoves();
            }
        }
    }
}




void chessGame::movePiece(int fromIndex, int toIndex) {

    if(m_board[fromIndex]->getType() == "King") {
        if( toIndex - fromIndex == 2) {
            castle(true);
        } else if ( toIndex - fromIndex == -2) {
            castle(false);
        }
        if(m_board[fromIndex]->getIsWhite()){m_whiteKingPosition = toIndex;} else {m_blackKingPosition = toIndex;}
    }

    m_board[fromIndex]->setIndex(toIndex);

    m_board[toIndex] = std::move(m_board[fromIndex]);
    m_board[fromIndex] = nullptr;



    m_whiteToMove = !m_whiteToMove;
    m_selected = 0;

    identifyMoves();

}




