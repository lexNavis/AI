#include <vector>
#include <queue>
#include <cstddef>
#include <climits>
#include <math.h>
#include <algorithm>
#include "AStar.h"
#include "../tree/Tree.h"
#include "SearchResult.h"

static int h(const Tree& tree, int current, int goal)
{
  int diff = tree.getNode(goal).depth - tree.getNode(current).depth;
  return std::max(0, diff) * MIN_COST;
}

SearchResult AStar(const Tree& tree, int start, int goal)
{
  std::vector<int> parent(tree.nodesCount(), -1);
  std::vector<int> g(tree.nodesCount(), INT_MAX);
  std::vector<bool> closed(tree.nodesCount(), false);
  std::vector<int> visited;
  std::priority_queue<AStarNode, std::vector<AStarNode>, CompareNode> open;
  if (start < 0 || start >= (int)tree.nodesCount() ||
      goal < 0 || goal >= (int)tree.nodesCount())
  {
    return {};
  }

  if (start == goal)
  {
    return {{start}, {start}, 0};
  }

  /* Настройка стартовых параметров */
  g[start] = 0;
  open.push(AStarNode{h(tree, start, goal), start});

  while (!open.empty())
  {
    /* Получаем вершину с наименьшей эвристикой */
    AStarNode current = open.top();
    open.pop();
    /* Если вершина уже просмотрена, то ее рассматривать не нужно */
    if (closed[current.id])
    {
      continue;
    }
    visited.push_back(current.id);
    if (current.id == goal)
    {
      /* Восстановление пути */
      std::vector<int> path;
      int v = goal;
      while (v != -1)
      {
        path.push_back(v);
        v = parent[v];
      }
      std::reverse(path.begin(), path.end());
      return {visited, path, g[goal]};
    }
    closed[current.id] = true;
    /* Проходим по её соседям */
    for (const Child &child : tree.getNode(current.id).children)
    {
      /* Если нашли стоимость меньше, чем указано у вершины,
       * обновим родителя и стоимость */
      if (g[current.id] + child.cost < g[child.id])
      {
        g[child.id] = g[current.id] + child.cost;
        parent[child.id] = current.id;
        /* Вершины с уменьшенной стоимостью снова попадают в очередь на переоценку */
        open.push(AStarNode{g[child.id] + h(tree, child.id, goal), child.id});
      }
    }
  }
  return {visited, {}, 0};
}