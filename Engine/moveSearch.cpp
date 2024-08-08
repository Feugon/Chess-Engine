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
        if(depth == 2) {
            std::cout << move.from << "->" << move.to << ": " << x << std::endl;
        }
        nodes += x;
        game.unmakeMove(move);
    }

    return nodes;
}

