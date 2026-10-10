#include "Tree.h"
#include "TreeGenerator.h"
#include <random>

Tree generateTree(int branchSize, int depth, int seed) {
    const int UTILITIES[] = {-10, -8, -5, -2, 0, 1, 3, 5, 7, 10};
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> cost(MIN_COST, MAX_COST);
    std::uniform_int_distribution<int> utilityIndex(0, sizeof(UTILITIES)/sizeof(UTILITIES[0]) - 1);

    std::vector<Node> nodes; 
    
    /* Создадим корень */
    Node root;
    root.id = 0;
    root.depth = 0;
    root.utility = 0;
    nodes.push_back(root);

    std::vector<int> currentLevel = {0};
    /* Цикл по высотам */
    for (int i = 0; i < depth; i++) {
        std::vector<int> nextLevel;
        /* Цикл по вершинам текущего уровня */
        for (int j : currentLevel) {
            /* Цикл по детям вершины */
            for (int k = 0;  k < branchSize; k++) {
                Node child;
                child.id = nodes.size();
                child.depth = i + 1;
                child.utility = 0;
                nextLevel.push_back(child.id);
                /* Добавим ребенка в общий вектор вершин */
                nodes.push_back(child);
                /* Добавляем детей */
                nodes[j].children.push_back(Child{child.id, cost(rng)});
            }
        }
        currentLevel = nextLevel;
    }
    /* Для листов получим ютилити */
    for (int i : currentLevel) {
        nodes[i].utility = UTILITIES[utilityIndex(rng)];
    }
    return Tree(nodes, 0);
}