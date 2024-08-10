#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


enum PieceType {
    king, queen, rook, bishop, knight, pawn, padding, piece
};

class basePiece {

public:

    basePiece(int position, bool is_white, PieceType type);
    virtual ~basePiece() = default;


    void draw(sf::RenderWindow& window);
    virtual void generateMoves(std::vector<std::unique_ptr<basePiece>> &board) = 0;


    virtual void move(int index);
    virtual void setIndex(int index){} // this will be deleted
    virtual bool inCheck(std::vector<std::unique_ptr<basePiece>> &board){return false;}


    int getPosition(){return m_position;}
    int getValue();
    void setValue(int value){m_value = value;}
    std::vector<int> getMoves(){return m_possibleMoves;}
    virtual PieceType getType(){return m_type;}
    virtual bool getIsWhite(){return m_isWhite;}

    static int m_whiteKingPosition;
    static int m_blackKingPosition;
    static int m_enPassantPosition;

protected:
    PieceType m_type = piece;
    bool m_isWhite;
    int m_position;
    int m_value;
    std::vector<int> m_positionBonus;
    std::string m_imageDir;
    std::vector<int> m_possibleMoves;



    std::vector<int> slidingMoves(std::vector<std::unique_ptr<basePiece>> &board, const std::vector<int> &shifts);
    bool isOccupiedByFriendly(const std::vector<std::unique_ptr<basePiece>> &board, int  index);
    bool isOccupiedByEnemy(const std::vector<std::unique_ptr<basePiece>> &board, int index);
    bool isSquareEmpty(const std::vector<std::unique_ptr<basePiece>>&board, int index);
    bool legalMove( std::vector<std::unique_ptr<basePiece>>&board, int from, int to);
};

