#include "Tree.h"

Tree::Tree(const std::vector<Node> &newNodes, int newRootId)
{
    m_nodes = newNodes;
    m_rootId = newRootId;
}

int Tree::rootId() const
{
    return m_rootId;
}
const std::vector<Node>& Tree::nodes() const
{
    return m_nodes;
}
const Node& Tree::getNode(int id) const
{
    return m_nodes[id];
}

size_t Tree::nodesCount() const
{
    return m_nodes.size();
}