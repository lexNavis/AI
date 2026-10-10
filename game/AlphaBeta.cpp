#include "../tree/Tree.h"
#include "AlphaBeta.h"
#include <vector>
#include <climits>

static int do_alphaBeta(
    const Tree &tree,
    int vertex,
    int alpha, int beta,
    std::vector<int> &visited,
    std::vector<int> &values,
    int &cutoffs)
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
     * нечетных - минимум.  */
    if (node.depth % 2 == 0)
    {
        int best = INT_MIN;
        for (const Child &child : node.children)
        {
            int cur = do_alphaBeta(tree, child.id, alpha, beta, visited, values, cutoffs);
            best = std::max(best, cur);
            /* После нахождения проверяем на целесообразность
             * дальнейшего просмотра ветки */
            alpha = std::max(best, alpha);
            if (alpha >= beta)
            {
                cutoffs++;
                break;
            }
        }
        values[node.id] = best;

        return best;
    }
    int best = INT_MAX;
    for (const Child &child : node.children)
    {
        int cur = do_alphaBeta(tree, child.id, alpha, beta, visited, values, cutoffs);
        best = std::min(best, cur);
        /* После нахождения проверяем на целесообразность
         * дальнейшего просмотра ветки */
        beta = std::min(best, beta);
        if (alpha >= beta)
        {
            cutoffs++;
            break;
        }
    }
    values[node.id] = best;
    return best;
}

GameResult alphaBeta(const Tree &tree)
{
    std::vector<int> visited;
    std::vector<int> values(tree.nodesCount(), -999);
    int cutoffs = 0;

    int rootVal = do_alphaBeta(tree, tree.rootId(), INT_MIN, INT_MAX, visited, values, cutoffs);
    /* Определим первый оптимальный ход */
    int bestMove = -1;
    for (const Child &child : tree.getNode(tree.rootId()).children)
    {
        if (values[child.id] == rootVal)
        {
            bestMove = child.id;
            break;
        }
    }
    /* Формируем результат */
    return {bestMove, visited, values, cutoffs};
}
