#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


enum PieceType {
    king, queen, rook, bishop, knight, pawn, padding, piece
};

/**
 * @class basePiece
 * @brief Base class for chess pieces, providing common functionality.
 */
class basePiece {
public:

    // constructor and destructor
    basePiece(int position, bool is_white, PieceType type);
    virtual ~basePiece() = default;

    /**
     * @brief Draws the piece on the SFML window.
     * @param window The window where the piece is drawn.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Generates all possible moves for the piece.
     * @param board The current board state.
    */
    virtual void generateMoves(std::vector<std::unique_ptr<basePiece>> &board) = 0;

    /**
         * @brief Moves the piece to a new position.
         * @param index The new position index.
    */
    virtual void move(int index);

    virtual void setIndex(int index){} // this should be rethought later

    /**
         * @brief Checks if the king is in check
         * @param board Current position
         * @return Boolean corresponding to if the king is in check
    */
    virtual bool inCheck(std::vector<std::unique_ptr<basePiece>> &board){return false;}

    //getters and setters
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


    /**
         * @brief Generates sliding moves based on shifts.
         * @param board The current position
         * @param shifts The directions to slide.
         * @return A vector of valid move indices.
         */
    std::vector<int> slidingMoves(std::vector<std::unique_ptr<basePiece>> &board, const std::vector<int> &shifts);

    /**
        * @brief Checks if a square is occupied by a friendly piece.
        * @param board The current position.
        * @param index The index to check.
        * @return True if occupied by a friendly piece, false otherwise.
        */
    bool isOccupiedByFriendly(const std::vector<std::unique_ptr<basePiece>> &board, int index);

    /**
     * @brief Checks if a square is occupied by an enemy piece.
     * @param board The current position.
     * @param index The index to check.
     * @return True if occupied by an enemy piece, false otherwise.
     */
    bool isOccupiedByEnemy(const std::vector<std::unique_ptr<basePiece>> &board, int index);

    /**
     * @brief Checks if a square is empty.
     * @param board The current board state.
     * @param index The index to check.
     * @return True if the square is empty, false otherwise.
     */
    bool isSquareEmpty(const std::vector<std::unique_ptr<basePiece>> &board, int index);

    /**
     * @brief Determines if a move is legal.
     * @param board The current position
     * @param from The starting position.
     * @param to The ending position.
     * @return True if the move is legal, false otherwise.
     */
    bool legalMove(std::vector<std::unique_ptr<basePiece>> &board, int from, int to);
};

