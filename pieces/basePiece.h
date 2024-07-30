#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


class basePiece {

public:

    basePiece(int position, bool is_white, std::string type);
    virtual ~basePiece() = default;

    void draw(sf::RenderWindow& window);
    virtual void generateMoves(const std::vector<std::unique_ptr<basePiece>> &board) = 0;
    std::vector<int> getMoves(){return m_possibleMoves;}

    virtual void setIndex(int index);
    virtual std::string getType(){return m_type;}
    virtual bool getIsWhite(){return m_isWhite;}

protected:
    std::string m_type = "BasePiece";
    bool m_isWhite;
    int m_position;
    std::string m_imageDir;
    std::vector<int> m_possibleMoves;

    std::vector<int> slidingMoves(const std::vector<std::unique_ptr<basePiece>> &board, const std::vector<int> &shifts);
    bool isOccupiedByFriendly(const std::vector<std::unique_ptr<basePiece>> &board, int  index);
    bool isOccupiedByEnemy(const std::vector<std::unique_ptr<basePiece>> &board, int index);
    bool isSquareEmpty(const std::vector<std::unique_ptr<basePiece>>&board, int index);
};