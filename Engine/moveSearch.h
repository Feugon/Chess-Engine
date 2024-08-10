#pragma once
#include "../GameOutput/gameClass.h"

int search(chessGame &game);

int perft(chessGame &game, int depth);

int evaluate(std::vector<std::unique_ptr<basePiece>> &board);

void playMoves(chessGame &game);

