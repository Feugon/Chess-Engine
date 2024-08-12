#include "basePiece.h"
#include <SFML/Graphics.hpp>
#include "../constants.h"


int basePiece::m_whiteKingPosition = 0;
int basePiece::m_blackKingPosition = 0;
int basePiece::m_enPassantPosition = 0;

basePiece::basePiece(int position, bool is_white, PieceType type) {
    m_position = position;
    m_isWhite = is_white;
    m_type = type;
}

void basePiece::move(int index) {
    basePiece::m_enPassantPosition = 0;
    m_position = index;
}

int basePiece::getValue() {
    // my bonus position vectors are only for white pieces so this flips it for black piece indices
    int reflectedPosition = m_isWhite ? m_position: (5 - m_position / 10) * 20 + 10 + m_position;
    return m_value + m_positionBonus[reflectedPosition];
}



bool basePiece::isOccupiedByFriendly(const std::vector<std::unique_ptr<basePiece>> &board, int index) {

    if (board[index] == nullptr) {return false;}
    if (board[index]->getType() == padding) {return true;}

    return board[index]->getIsWhite() == m_isWhite;

}


bool basePiece::isSquareEmpty(const std::vector<std::unique_ptr<basePiece>> &board, int index) {
    return board[index] == nullptr;
}

bool basePiece::isOccupiedByEnemy(const std::vector<std::unique_ptr<basePiece>> &board, int index) {

    if(board[index] == nullptr) {
        return false;
    } else if(m_isWhite) {
        if(!board[index]->getIsWhite() && board[index]->getType() != padding) {
            return true;
        } else {
            return false;
        }
    } else {
        if(board[index]->getIsWhite() && board[index]->getType() != padding) {
            return true;
        } else {
            return false;
        }
    }
}



std::vector<int> basePiece::slidingMoves(std::vector<std::unique_ptr<basePiece>> &board, const std::vector<int> &shifts) {

    std::vector<int> possibleMoves;

    if(m_type != king) {
        for(int shift: shifts) {
            int distance = 1;
            while(true) {
                if(isOccupiedByFriendly(board,m_position + distance * shift)) {
                    break;
                } else if(isOccupiedByEnemy(board, m_position + distance * shift)) {
                    if(legalMove(board, m_position,m_position + distance * shift)) {
                        possibleMoves.push_back(m_position + distance * shift);
                    }
                    break;
                } else if(legalMove(board, m_position,m_position + distance * shift)){
                    possibleMoves.push_back(m_position + distance * shift);
                    distance++;
                } else {
                    distance++; // this is a bad idea
                }
            }
        }
    } else if (m_type == king){
        for(int shift: shifts) {
            int distance = 1;
            while(true) {
                if(isOccupiedByFriendly(board,m_position + distance * shift)) {
                    break;
                } else if(isOccupiedByEnemy(board, m_position + distance * shift)) {
                    possibleMoves.push_back(m_position + distance * shift);
                    break;
                } else {
                    possibleMoves.push_back(m_position + distance * shift);
                    distance++;
                }
            }
        }
    }

    return possibleMoves;
}



bool basePiece::legalMove(std::vector<std::unique_ptr<basePiece>> &board, int from, int to) {

    bool isLegalMove;

    // move the pieces in the pointer board
    std::unique_ptr<basePiece> captured = std::move(board[to]);
    board[to] = std::move(board[from]);
    board[from] = nullptr;


    if(m_isWhite) {
        if (board[to]->getType() == pawn && (from + 1 == m_enPassantPosition || from - 1 == m_enPassantPosition) && to%10 == m_enPassantPosition%10) {
            std::unique_ptr<basePiece> enPassantPawn = std::move(board[m_enPassantPosition]);
            board[m_enPassantPosition] = nullptr;
            isLegalMove = !(board[m_whiteKingPosition]->inCheck(board));
            board[m_enPassantPosition] = std::move(enPassantPawn);
        } else if(board[to]->getType() != king) {
            isLegalMove = !(board[m_whiteKingPosition]->inCheck(board));
        } else {
            board[to]->setIndex(to);                        // this changes position member
            isLegalMove = !(board[to]->inCheck(board));
            board[to]->setIndex(from);                     // this undoes the m_position change
        }
    } else {
        if (board[to]->getType() == pawn && (from + 1 == m_enPassantPosition || from - 1 == m_enPassantPosition) && to%10 == m_enPassantPosition%10) {
            std::unique_ptr<basePiece> enPassantPawn = std::move(board[m_enPassantPosition]);
            board[m_enPassantPosition] = nullptr;
            isLegalMove = !(board[m_blackKingPosition]->inCheck(board));
            board[m_enPassantPosition] = std::move(enPassantPawn);
        } else if(board[to]->getType() != king) {
            isLegalMove = !(board[m_blackKingPosition]->inCheck(board));
        } else {
            board[to]->setIndex(to);                        // this changes position member
            isLegalMove = !(board[to]->inCheck(board));
            board[to]->setIndex(from);                     // this undoes the m_position change
        }
    }

    // undo the move
    board[from] = std::move(board[to]);
    board[to] = std::move(captured);


    return isLegalMove;
}






void basePiece::draw(sf::RenderWindow& window) {

    sf::Texture texture;
    texture.loadFromFile(m_imageDir);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    int y_cord = m_position / 10 - 2;
    int x_cord = m_position % 10 - 1;

    // Magic numbers for display purposes
    sprite.setPosition(x_cord * constants::TILE_WIDTH + 2, y_cord * constants::TILE_HEIGHT + 2);
    sprite.scale(1.2, 1.2);
    window.draw(sprite);
}
