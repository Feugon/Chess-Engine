#pragma once
#include "gameClass.h"



/**
 * @brief Implements the minimax algorithm with alpha-beta pruning to evaluate and select the best move.
 * @param game The game object
 * @param depth The remaining depth to search. A depth of 0 indicates the base case of the recursion.
 * @param maximizingPlayer A boolean indicating whether the current player is the maximizing player (true) or minimizing player (false).
 * @param bestMove A reference to a Move object where the best move will be stored.
 * @param alpha The best value that the maximizing player can guarantee so far (for alpha-beta pruning).
 * @param beta The best value that the minimizing player can guarantee so far (for alpha-beta pruning).
 * @return The evaluated score of the game state from the perspective of the current player.
 */
int minimax(chessGame &game, int depth, bool maximizingPlayer, Move &bestMove, int alpha, int beta);

/**
     * @brief Evaluates a position, higher numbers being good for white and lower for black
     * @param board A vector of pointers reflecting the current position
     * @return An integer evaluation
*/
int evaluate(std::vector<std::unique_ptr<basePiece>> &board);

/**
     * @brief Calculates every move possible to make up to a certain depth
     * @param game The game object
     * @param depth The depth to which moves should be calculated.
     * @return The number of possible moves
*/
int perft(chessGame &game, int depth);
