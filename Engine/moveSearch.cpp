#include "moveSearch.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

//Logic based on this -> https://www.chessprogramming.org/Perft

int minimax(chessGame &game, int depth, bool maximizingPlayer, Move &bestMove, int alpha, int beta) {
    if (depth == 0 || game.getGameOver()) {
        return evaluate(game.m_board);
    }

    std::vector<Move> possibleMoves = game.getMoves();

    if (maximizingPlayer) {
        int maxEval = -1e9;  // negative infinity
        for (auto &move : possibleMoves) {
            game.makeMove(move);
            Move tempBestMove;
            int eval = minimax(game, depth - 1, false, tempBestMove, alpha, beta);
            game.unmakeMove(move);

            if (eval > maxEval) {
                maxEval = eval;
                bestMove = move;
            }

            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;

    } else {
        int minEval = 1e9;  // positive infinity
        for (auto &move : possibleMoves) {
            game.makeMove(move);
            Move tempBestMove;
            int eval = minimax(game, depth - 1, true, tempBestMove, alpha, beta);
            game.unmakeMove(move);

            if (eval < minEval) {
                minEval = eval;
                bestMove = move;
            }

            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}




// for performance testing
int perft(chessGame &game, int depth) {
    unsigned long long nodes = 0;

    if(depth == 0) {
        return 1;
    }

    std::vector<Move> possibleMoves = game.getMoves();

    for(auto& move: possibleMoves) {
        game.makeMove(move, depth - 1);
        int x = perft(game, depth - 1);
        /*
        if(depth == 2) {
            std::cout << move.from << "->" << move.to << ": " << x << std::endl;
        }
        */
        nodes += x;
        game.unmakeMove(move);
    }

    return nodes;
}

int evaluate(std::vector<std::unique_ptr<basePiece>> &board) {
    int whiteMaterial = 0;
    int blackMaterial = 0;

    for (int i = 21; i <= 98; i ++) {
        if(board[i] == nullptr || board[i]->getType() == padding) {
            continue;
        } else if (board[i]->getIsWhite()) {
            whiteMaterial += board[i]->getValue();
        } else {
            blackMaterial += board[i]->getValue();
        }
    }

    return whiteMaterial - blackMaterial;
}



void playMoves(chessGame &game) {
    std::vector<Move> possibleMoves = game.getMoves();
    int randomIndex = 0 + std::rand() % (possibleMoves.size());
    game.makeMove(possibleMoves[randomIndex]);

}



