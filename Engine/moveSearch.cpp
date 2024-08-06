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

    std::vector<Move> possibleMoves = game.getMoves(depth);

    for(auto& move: possibleMoves) {
        game.makeMove(move);
        nodes += perft(game, depth - 1);
        game.unmakeMove(move);
    }

    return nodes;
}

