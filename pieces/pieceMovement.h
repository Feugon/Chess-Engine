#pragma once
#include <vector>

bool isOccupiedByFriendly(const std::vector<int> &board, int index,  bool isWhite);

bool isOccupiedByEnemy(const std::vector<int> &board, int index, bool isWhite);

bool isSquareEmpty(const std::vector<int> &board, int index);

std::vector<int> slidingMoves(const std::vector<int> &board, int index, bool isWhite, const std::vector<int> &shifts);