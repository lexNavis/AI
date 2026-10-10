#pragma once
#include <vector>

struct GameResult {
    int bestMove;
    std::vector<int> visited;
    std::vector<int> values;
    int cutoffs;
};