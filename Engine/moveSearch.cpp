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
        //make move
        nodes += perft(game, depth - 1);
        //unod move
    }

    return nodes;
}

