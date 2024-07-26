#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


class basePiece {


public:
    basePiece(int position, bool is_white);
    void draw(sf::RenderWindow& window);
    virtual std::vector<int> generateMoves(const std::vector<int> &board) = 0;

protected:

    bool m_isWhite;
    int m_position;
    std::string m_imageDir;

    std::vector<int> slidingMoves(const std::vector<int> &board, const std::vector<int> &shifts);
    bool isOccupiedByFriendly(const std::vector<int> &board, int  index);
    bool isOccupiedByEnemy(const std::vector<int> &board, int index);
    bool isSquareEmpty(const std::vector<int> &board, int index);
};