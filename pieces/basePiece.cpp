#include "basePiece.h"
#include <SFML/Graphics.hpp>
#include "../constants.h"


basePiece::basePiece(int position, bool is_white, std::string type) {
    m_position = position;
    m_isWhite = is_white;
    m_type = type;
}

void basePiece::setIndex(int index) {
    m_position = index;
}


bool basePiece::isOccupiedByFriendly(const std::vector<std::unique_ptr<basePiece>> &board, int index) {
    bool occupiedByFriend;


    if (board[index] == nullptr) {
        return false;
    } else if (m_isWhite) {
        if (board[index]->getIsWhite() || board[index]->getType() == "Padding") {
            occupiedByFriend = true;
        } else {
            occupiedByFriend = false;
        }
    } else {
        if (!board[index]->getIsWhite() || board[index]->getType() == "Padding") {
            occupiedByFriend = true;
        } else {
            occupiedByFriend = false;
        }
    }

    return occupiedByFriend;
}


bool basePiece::isSquareEmpty(const std::vector<std::unique_ptr<basePiece>> &board, int index) {
    return board[index] == nullptr;
}

bool basePiece::isOccupiedByEnemy(const std::vector<std::unique_ptr<basePiece>> &board, int index) {

    if(board[index] == nullptr) {
        return false;
    } else if(m_isWhite) {
        if(!board[index]->getIsWhite() || board[index]->getType() == "Padding") {  // this could point to a nullptr and crash the program
            return true;
        } else {
            return false;
        }
    } else {
        if(board[index]->getIsWhite() || board[index]->getType() == "Padding") {
            return true;
        } else {
            return false;
        }
    }
}



std::vector<int> basePiece::slidingMoves(const std::vector<std::unique_ptr<basePiece>> &board, const std::vector<int> &shifts) {

    std::vector<int> possibleMoves;

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

    return possibleMoves;
}



void basePiece::draw(sf::RenderWindow& window) {

    sf::Texture texture;
    texture.loadFromFile(m_imageDir);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    int y_cord = m_position / 10 - 2;
    int x_cord = m_position % 10 - 1;


    // TODO figure out the equation for the buffer here...
    sprite.setPosition(x_cord * constants::TILE_WIDTH + 2, y_cord * constants::TILE_HEIGHT + 2);
    sprite.scale(1.2, 1.2);
    window.draw(sprite);
}
