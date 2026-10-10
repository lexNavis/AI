#include "experiments/Experiment.h"
#include <iostream>

int main()
{
    std::cout << "=====================\n";
    std::cout << "SMALL TREE (b=2, d=2)\n";
    std::cout << "=====================\n";
    run_search_tests(2, 2, 42, 0, 6, 5);
    run_game_tests(2, 2, 42, 5);

    std::cout << "\n=====================\n";
    std::cout << "MEDIUM TREE (b=3, d=4)\n";
    std::cout << "=====================\n";
    run_search_tests(3, 4, 42, 0, 120, 5);
    run_game_tests(3, 4, 42, 5);

    std::cout << "\n=====================\n";
    std::cout << "LARGE TREE (b=4, d=5)\n";
    std::cout << "=====================\n";
    run_search_tests(4, 5, 42, 0, 1364, 5);
    run_game_tests(4, 5, 42, 5);

    return 0;
}