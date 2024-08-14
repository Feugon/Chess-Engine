#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <memory>
#include <unordered_set>
#include <stack>
#include "pieces/basePiece.h"


struct Move {
    int from;
    int to;
};

/**
 * @class chessGame
 * @brief Manages the state and logic of a chess game.
 */
class chessGame {
public:
    /**
     * @brief Constructor that initializes the chess game using a FEN string.
     * @param FEN A string representing the initial position in FEN notation.
     */
    chessGame(const std::string &FEN);

    /**
     * @brief Draws the current position on the chessboard.
     * @param window The SFML window where the position is drawn.
     */
    void drawPosition(sf::RenderWindow &window);

    /**
     * @brief Draws possible moves for the selected piece.
     * @param window The SFML window where the moves are drawn.
     */
    void drawPossibleMoves(sf::RenderWindow &window);

    /**
     * @brief Sets the selected piece based on mouse coordinates.
     * @param mouseX The X-coordinate of the mouse.
     * @param mouseY The Y-coordinate of the mouse.
     */
    void selectedSetter(int mouseX, int mouseY);

    /**
     * @brief Executes a move on the chessboard.
     * @param move The move to be made.
     * @param depth (Optional) Depth of the move stack; used for move unmaking.
     */
    void makeMove(Move move, int depth = 1);

    /**
     * @brief Undoes the last move made on the chessboard.
     * @param move The move to be undone.
     */
    void unmakeMove(Move move);

    /**
     * @brief Retrieves a list of all possible moves for the current player.
     * @return A vector of possible moves.
     */
    std::vector<Move> getMoves();

    /**
     * @brief Identifies and generates all possible moves for the current game state.
     */
    void identifyMoves();

    /**
     * @brief Checks if the game is over
     * @return True if the game is over, false otherwise.
     */
    bool getGameOver() { return m_checkmate || m_stalemate; }

    /**
     * @brief Checks if it is White's turn to move.
     * @return True if it is White's turn, false if it is Black's turn.
     */
    bool getWhiteToMove() { return m_whiteToMove; }

    /**
     * @brief The current state of the chessboard, represented as a vector of unique pointers to chess pieces.
     */
    std::vector<std::unique_ptr<basePiece>> m_board;

    Move m_lastMove; // should delete this at some point

private:
    bool m_checkmate = false;
    bool m_stalemate = false;
    int m_selected;
    int m_lastSelected;
    int m_whiteKingPosition;
    int m_blackKingPosition;
    bool m_whiteToMove;
    Move m_lastPromotionMove;
    std::vector<int> m_moveChoices;
    std::vector<Move> m_whiteMoves;
    std::vector<Move> m_blackMoves;
    std::stack<std::unique_ptr<basePiece>> m_lastOccupied;
    std::unique_ptr<basePiece> m_enPassantedPawn;

    /**
     * @brief Executes castling on the chessboard.
     * @param kingsideCastle Indicates whether the castling is kingside (true) or queenside (false).
     */
    void castle(bool kingsideCastle);
};
