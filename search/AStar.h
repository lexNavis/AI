#pragma once

class Tree;
struct SearchResult;

struct AStarNode {
    int f;
    int id;
};

struct CompareNode {
    bool operator()(const AStarNode& a, const AStarNode& b) const {
        return a.f > b.f;
    }
};

SearchResult AStar(const Tree &tree, int start, int goal);
