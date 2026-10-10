#include "BFS.h"
#include <algorithm>
#include <queue>

SearchResult BFS(const Tree &tree, int start, int goal)
{
  if (start < 0 || (unsigned int)start >= tree.nodesCount() || goal < 0 || (unsigned int)goal >= tree.nodesCount())
  {
    return {{}, {}, 0};
  }

  if (start == goal) return {{start}, {start}, 0};
  
  std::vector<int> visited;
  std::vector<int> parent(tree.nodesCount(), -1);
  std::queue<int> q;

  /* Положим корень как стартовую вершину */
  q.push(start);

  while (!q.empty())
  {
    int current = q.front();
    q.pop();
    visited.push_back(current);
    /* Если дошли до цели, то восстановим путь и вернем посещенные вершины */
    if (current == goal)
    {
      std::vector<int> path;
      int end = goal;
      while (end != -1)
      {
        path.push_back(end);
        end = parent[end];
      }
      std::reverse(path.begin(), path.end());
      return {visited, path, 0};
    }
    /* Пройдемся по детям текущей вершины */
    for (const Child& child : tree.getNode(current).children)
    {
      /* Проверка, попадали ли мы уже в текущую вершину (для дерева невозможно)*/
      if (parent[child.id] == -1) {
          parent[child.id] = current;
          q.push(child.id);
      }
    }
  }
  return {visited, {}, 0};
}