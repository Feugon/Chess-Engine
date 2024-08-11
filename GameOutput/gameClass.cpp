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
            auto paddingPointer = std::make_unique<Padding>(i, false, padding);
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
                auto pawnPointer = std::make_unique<Pawn>(i, is_white, pawn);
                m_board.push_back(std::move(pawnPointer));
            } else if (FEN[stringIndex] == 'n' || FEN[stringIndex] == 'N') {
                // Handle Knight
                auto knightPointer = std::make_unique<Knight>(i, is_white, knight);
                m_board.push_back(std::move(knightPointer));
            } else if (FEN[stringIndex] == 'b' || FEN[stringIndex] == 'B') {
                // Handle Bishop
                auto bishopPointer = std::make_unique<Bishop>(i, is_white, bishop);
                m_board.push_back(std::move(bishopPointer));
            } else if (FEN[stringIndex] == 'r' || FEN[stringIndex] == 'R') {
                // Handle Rook
                auto rookPointer = std::make_unique<Rook>(i, is_white, rook);
                m_board.push_back(std::move(rookPointer));
            } else if (FEN[stringIndex] == 'q' || FEN[stringIndex] == 'Q') {
                // Handle Queen
                auto queenPointer = std::make_unique<Queen>(i, is_white,queen);
                m_board.push_back(std::move(queenPointer));
            } else if (FEN[stringIndex] == 'k' || FEN[stringIndex] == 'K') {
                // Handle King
                auto kingPointer = std::make_unique<King>(i, is_white, king);
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
        if(pointer && pointer->getType() != padding) {
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
        makeMove({m_lastSelected,m_selected});
        m_selected = 0;
    }

    m_moveChoices.clear();

    // if we select the right colored piece then gets its possible moves
    if(m_board[m_selected]) {
        if((m_board[m_selected]->getIsWhite() && m_whiteToMove)) {
            m_moveChoices = m_board[m_selected]->getMoves();
        } else if ( (!m_board[m_selected]->getIsWhite() && !m_whiteToMove)) {
            m_moveChoices = m_board[m_selected]->getMoves();
        }
    }

    m_lastSelected = m_selected;
}


void chessGame::castle(bool kingsideCastle) {
    int kingPosition = m_whiteToMove ? m_whiteKingPosition : m_blackKingPosition;
    if(kingsideCastle) {
        m_board[kingPosition + 3]->move(kingPosition + 1);
        m_board[kingPosition + 1] = std::move(m_board[kingPosition + 3]);
        m_board[kingPosition + 3] = nullptr;
    } else {
        m_board[kingPosition - 4]->move(kingPosition - 1);
        m_board[kingPosition- 1] = std::move(m_board[kingPosition - 4]);
        m_board[kingPosition - 4] = nullptr;
    }
}


void chessGame::identifyMoves() {
    m_whiteMoves.clear();
    m_blackMoves.clear();
    bool hasMoves = false; // somehow its faster to use this over .empty()

    if(!m_checkmate && !m_stalemate) {
        for (int i = 21; i <= 98; i ++) {
            if(m_board[i] != nullptr){
                if(m_board[i]->getIsWhite() && m_whiteToMove) {
                    m_board[i]->generateMoves(m_board);
                    for (auto move : m_board[i]->getMoves()) {
                        hasMoves = true;
                        m_whiteMoves.push_back({m_board[i]->getPosition(),move});
                    }
                } else if (!m_board[i]->getIsWhite() && !m_whiteToMove) {
                    m_board[i]->generateMoves(m_board);
                    for (auto move : m_board[i]->getMoves()) {
                        hasMoves = true;
                        m_blackMoves.push_back({m_board[i]->getPosition(),move});
                    }
                }
            }
        }
    }


    //checkmate detection
    if(!hasMoves &&  m_board[m_whiteKingPosition]->inCheck(m_board)) {
        m_board[m_whiteKingPosition]->setValue(-100000); // this is for evaluation purposes, nothing is better than mate
        m_checkmate = true;
    } else if (!hasMoves  && m_board[m_blackKingPosition]->inCheck(m_board)) {
        m_board[m_whiteKingPosition]->setValue(100000);
        m_checkmate = true;
    } else if (!hasMoves) {
        m_stalemate = true;
    } else {
        //undo the checkmate evaluations
        m_board[m_whiteKingPosition]->setValue(0);
        m_board[m_whiteKingPosition]->setValue(0);
    }


}

std::vector<Move> chessGame::getMoves() {


     if(m_whiteToMove) {
         return m_whiteMoves;
    } else {
        return m_blackMoves;
    }
}



void chessGame::makeMove(Move move, int depth) {

    m_lastMove = move;
    m_lastOccupied.push(std::move(m_board[move.to]));
    m_lastMoveWasPromotion = false;

    // check for castling logic
    if(m_board[move.from]->getType() == king) {
        if( move.to - move.from == 2) {
            castle(true);
        } else if ( move.to - move.from == -2) {
            castle(false);
        }

        if(m_board[move.from]->getIsWhite()) {
            m_whiteKingPosition = move.to;
        } else {
            m_blackKingPosition = move.to;
        }
        m_board[move.from]->move(move.to);
        m_board[move.to] = std::move(m_board[move.from]);
        m_board[move.from] = nullptr;


    // handles promotion (defaults to queen, should add other pieces at some point)
    } else if(m_board[move.from]->getType() == pawn && (move.to / 10 == 2 || move.to / 10 == 9)) {
        m_lastMoveWasPromotion = true;
        if(move.to / 10 == 2 && m_board[move.from]->getIsWhite()) {
            auto queenPointer = std::make_unique<Queen>(move.to,true,queen);
            m_board[move.to] = std::move(queenPointer);
            m_board[move.from] = nullptr;
        } else if (move.to / 10 == 9 && !(m_board[move.from]->getIsWhite())) {
            auto queenPointer = std::make_unique<Queen>(move.to,false,queen);
            m_board[move.to] = std::move(queenPointer);
            m_board[move.from] = nullptr;
        }
    // handles en Passant (this should be cleaned up)
    } else if(m_board[move.from]->getType() == pawn && move.to % 10 != move.from % 10 && m_lastOccupied.top() == nullptr) {
        if(move.from - move.to == 9) {
            m_enPassantedPawn = std::move(m_board[move.from + 1]);
            m_board[move.from + 1] = nullptr;
        } else if (move.from - move.to == 11) {
            m_enPassantedPawn = std::move(m_board[move.from - 1]);
            m_board[move.from - 1] = nullptr;
        } else if(move.from - move.to == -9) {
            m_enPassantedPawn = std::move(m_board[move.from - 1]);
            m_board[move.from - 1] = nullptr;
        } else if (move.from - move.to == -11) {
            m_enPassantedPawn = std::move(m_board[move.from + 1]);
            m_board[move.from + 1] = nullptr;
        }
        m_board[move.from]->move(move.to);
        m_board[move.to] = std::move(m_board[move.from]);
        m_board[move.from] = nullptr;

    } else {
        m_board[move.from]->move(move.to);
        m_board[move.to] = std::move(m_board[move.from]);
        m_board[move.from] = nullptr;
    }

    m_whiteToMove = !m_whiteToMove;

    if(depth != 0) {
    identifyMoves();
    }



}



void chessGame::unmakeMove(Move move) {

    // check for castling logic
    if(m_board[move.to]->getType() == king) {
        //moves the rook back
        if(move.to - move.from == 2) {
            Rook* derived = static_cast<Rook*>(m_board[move.from + 1].get());
            derived->m_timesMoved -= 2;
            m_board[move.from + 1]->move(move.from + 3);
            m_board[move.from + 3] = std::move(m_board[move.from + 1]);
            m_board[move.from + 1] == nullptr;
        } else if ( move.to - move.from == -2) {
            Rook* derived = static_cast<Rook*>(m_board[move.from - 1].get());
            derived->m_timesMoved -= 2;
            m_board[move.from - 1]->move(move.from - 4);
            m_board[move.from - 4] = std::move(m_board[move.from - 1]);
            m_board[move.from - 1] == nullptr;
        }

        if(m_board[move.to]->getIsWhite()) {
            m_whiteKingPosition = move.from;
        } else {
            m_blackKingPosition = move.from;
        }
        King* derived = static_cast<King*>(m_board[move.to].get());
        derived->m_timesMoved -= 2;
        m_board[move.to]->move(move.from);
        m_board[move.from] = std::move(m_board[move.to]);
        m_board[move.to] = std::move(m_lastOccupied.top());
        m_lastOccupied.pop();

        // undoes promotion
        // note to self: the pawn can't move after getting created, but I don't think that should be an issue
    } else if(m_lastMoveWasPromotion) {
        if(move.to / 10 == 2 && m_board[move.to]->getIsWhite()) {
            auto pawnPointer = std::make_unique<Pawn>(move.from,true,pawn);
            m_board[move.from] = std::move(pawnPointer);
            m_board[move.to] = std::move(m_lastOccupied.top());
            m_lastOccupied.pop();
        } else if (move.to / 10 == 9 && !(m_board[move.from]->getIsWhite())) {
            auto pawnPointer = std::make_unique<Pawn>(move.from,false,pawn);
            m_board[move.from] = std::move(pawnPointer);
            m_board[move.to] = std::move(m_lastOccupied.top());
            m_lastOccupied.pop();
        }
    // undo en Passant
    } else if(m_board[move.to]->getType() == pawn && move.to % 10 != move.from % 10 && m_lastOccupied.top() == nullptr) {
        if(move.from - move.to == 9) {
            m_board[move.from + 1] = std::move(m_enPassantedPawn);
        } else if (move.from - move.to == 11) {
            m_board[move.from - 1] = std::move(m_enPassantedPawn);
        } else if(move.from - move.to == -9) {
            m_board[move.from - 1] = std::move(m_enPassantedPawn);
        } else if (move.from - move.to == -11) {
            m_board[move.from + 1] = std::move(m_enPassantedPawn);
        }
        m_board[move.to]->move(move.from);
        m_board[move.from] = std::move(m_board[move.to]);
        m_board[move.to] = std::move(m_lastOccupied.top());
        m_lastOccupied.pop();

    } else {
        if(m_board[move.to]->getType() == rook) {
            Rook* derived = static_cast<Rook*>(m_board[move.to].get());
            derived->m_timesMoved -= 2;
        }
        m_board[move.to]->move(move.from);
        m_board[move.from] = std::move(m_board[move.to]);
        m_board[move.to] = std::move(m_lastOccupied.top());
        m_lastOccupied.pop();

    }


    m_checkmate = false;
    m_stalemate = false;
    m_whiteToMove = !m_whiteToMove;
    m_selected = 0;

}



/*
21 22 23 24 25 26 27 28
31 32 33 34 35 36 37 38
41 42 43 44 45 46 47 48
51 52 53 54 55 56 57 58
61 62 63 64 65 66 67 68
71 72 73 74 75 76 77 78
81 82 83 84 85 86 87 88
91 92 93 94 95 96 97 98
*/

