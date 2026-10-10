#pragma once
#include <chrono>
#include <utility>   // ← pair, make_pair, forward

template<typename Func, typename... Args>
auto calcTime(Func f, Args&&... args) {
    auto start = std::chrono::steady_clock::now();
    auto result = f(std::forward<Args>(args)...);
    auto end = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return std::make_pair(ms, result);
}

void run_search_tests(int b, int d, unsigned seed, int start, int goal, int repeats = 5);
void run_game_tests(int b, int d, unsigned seed, int repeats = 5);