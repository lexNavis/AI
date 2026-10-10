#include "DFS.h"
#include <algorithm>

static bool do_DFS(
    const Tree &tree,
    int currentId,
    int goal,
    std::vector<int> &visited,
    std::vector<int> &parent)
{
  const Node &node = tree.getNode(currentId);
  visited.push_back(node.id);
  if (node.id == goal)
    return true;

  for (const Child &child : node.children)
  {
    parent[child.id] = node.id;
    if (do_DFS(tree, child.id, goal, visited, parent))
      return true;
  }
  return false;
}

SearchResult DFS(const Tree& tree, int start, int goal)
{
  if (start < 0 || (unsigned int)start >= tree.nodesCount() || goal < 0 || (unsigned int)goal >= tree.nodesCount())
  {
    return {{}, {}, 0};
  }
  std::vector<int> visited;
  std::vector<int> parent(tree.nodesCount(), -1);
  bool found = do_DFS(tree, start, goal, visited, parent);
  if (!found)
  {
    return {visited, {}, 0};
  }
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