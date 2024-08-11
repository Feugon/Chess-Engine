#pragma once
#include "../GameOutput/gameClass.h"

int minimax(chessGame &game, int depth, bool maximizingPlayer, Move &bestMove);

int perft(chessGame &game, int depth);

int evaluate(std::vector<std::unique_ptr<basePiece>> &board);

void playMoves(chessGame &game);

