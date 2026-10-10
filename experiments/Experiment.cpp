#include <iostream>
#include <iomanip>
#include "Experiment.h"
#include "../tree/TreeGenerator.h"
#include "../tree/Tree.h"
#include "../search/SearchResult.h"
#include "../search/DFS.h"
#include "../search/BFS.h"
#include "../search/AStar.h"
#include "../game/GameResult.h"
#include "../game/AlphaBeta.h"
#include "../game/Minimax.h"

void run_search_tests(int b, int d, unsigned seed, int start, int goal, int repeats)
{
  using SearchFunc = SearchResult (*)(const Tree &, int, int);
  SearchFunc searchFuncs[] = {DFS, BFS, AStar};
  const char *names[] = {"DFS", "BFS", "AStar"};

  Tree tree = generateTree(b, d, seed);
  int n = (int)tree.nodesCount();

  std::cout << "\n=== Search tests: b=" << b
            << " d=" << d
            << " seed=" << seed
            << " start=" << start
            << " goal=" << goal
            << " repeats=" << repeats << " ===\n";

  for (int i = 0; i < 3; i++)
  {
    SearchResult r;
    long long totalMs = 0;

    for (int j = 0; j < repeats; j++)
    {
      auto [ms, cur] = calcTime(searchFuncs[i], tree, start, goal);
      totalMs += ms;
      r = cur;
    }

    long long avgMs = totalMs / repeats;
    std::cout << std::setw(6) << "N"
              << std::setw(10) << "Алгоритм"
              << std::setw(10) << "Visited"
              << std::setw(10) << "Path"
              << std::setw(8) << "Cost"
              << std::setw(10) << "Time(ms)" << "\n";

    std::cout << std::setw(6) << n
              << std::setw(10) << names[i]
              << std::setw(10) << r.visited.size()
              << std::setw(10) << r.path.size()
              << std::setw(8) << r.cost
              << std::setw(10) << avgMs << "\n";
  }
}

void run_game_tests(int b, int d, unsigned seed, int repeats)
{
  using GameFunc = GameResult (*)(const Tree &);
  GameFunc gameFuncs[] = {minimax, alphaBeta};
  const char *names[] = {"Minimax", "AlphaBeta"};

  Tree tree = generateTree(b, d, seed);
  int n = (int)tree.nodesCount();

  std::cout << "\n=== Game tests: b=" << b
            << " d=" << d
            << " seed=" << seed
            << " repeats=" << repeats << " ===\n";

  for (int i = 0; i < 2; i++)
  {
    GameResult r;
    long long totalMs = 0;

    for (int j = 0; j < repeats; j++)
    {
      auto [ms, cur] = calcTime(gameFuncs[i], tree);
      totalMs += ms;
      r = cur;
    }

    long long avgMs = totalMs / repeats;

    std::cout << std::setw(6) << "N"
              << std::setw(12) << "Алгоритм"
              << std::setw(12) << "Листьев"
              << std::setw(12) << "Отсечено"
              << std::setw(14) << "Root value"
              << std::setw(14) << "Time(ms)" << "\n";
    std::cout << std::setw(6) << n
              << std::setw(12) << names[i]
              << std::setw(12) << r.visited.size()
              << std::setw(12) << r.cutoffs
              << std::setw(14) << r.values[tree.rootId()]
              << std::setw(14) << avgMs << "\n";
  }
}