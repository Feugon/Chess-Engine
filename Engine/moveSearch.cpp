#include "moveSearch.h"
#include <vector>
#include <unordered_map>

//Logic based on this -> https://www.chessprogramming.org/Perft

int search(chessGame &game) {

}


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



