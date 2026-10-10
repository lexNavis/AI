#include <climits>
#include "Minimax.h"
#include "../tree/Tree.h"

static int do_minimax(
    const Tree &tree,
    int vertex,
    std::vector<int> &visited,
    std::vector<int> &values)
{
    /* У листа возврат utility */
    const Node &node = tree.getNode(vertex);
    if (node.children.empty())
    {
        visited.push_back(vertex);
        values[vertex] = node.utility;
        return node.utility;
    }
    /* Проверка четности высоты: для родителя
     * с четной высотой ищем максимум, для
     * нечетных - минимум */
    if (node.depth % 2 == 0)
    {
        int best = INT_MIN;
        for (const Child &child : node.children)
        {
            int cur = do_minimax(tree, child.id, visited, values);
            best = std::max(best, cur);
        }
        values[node.id] = best;
        return best;
    }
    int best = INT_MAX;
    for (const Child &child : node.children)
    {
        int cur = do_minimax(tree, child.id, visited, values);
        best = std::min(best, cur);
    }
    values[node.id] = best;
    return best;
}

GameResult minimax(const Tree &tree)
{
    std::vector<int> visited;
    std::vector<int> values(tree.nodesCount(), -999);

    int rootVal = do_minimax(tree, tree.rootId(), visited, values);
    /* Определим первый оптимальный ход */
    int bestMove = -1;
    for (const Child& child : tree.getNode(tree.rootId()).children) {
        if (values[child.id] == rootVal) {
            bestMove = child.id;
            break;
        }
    }
    /* Формируем результат */
    return {bestMove, visited, values, 0};
}