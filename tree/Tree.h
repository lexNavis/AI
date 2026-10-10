#pragma once
#include <vector>
#include <cstddef>

#define MIN_COST 1
#define MAX_COST 10

struct Child
{
    int id;   /* Собственный идентификатор */
    int cost; /* Стоимость ребра */
};

struct Node
{
    int id;
    std::vector<Child> children;
    int depth;
    int utility;
};

class Tree
{
  public:
    Tree(const std::vector<Node>& newNodes, int newRootId);
    int rootId() const;
    const std::vector<Node>& nodes() const;
    const Node& getNode(int id) const;
    size_t nodesCount() const;
  private:
    int m_rootId;
    std::vector<Node> m_nodes;
};
