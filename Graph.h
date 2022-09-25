#ifndef AGENTPROJECT_GRAPH_H
#define AGENTPROJECT_GRAPH_H

#include <utility>
#include <vector>
#include "Map.h"

class Graph {
private:
    class Node{
    public:
        int cost = 1;
        Node(std::pair<int, int> data, std::vector<Node*> child_list = {})
                : location(std::move(data)){};

        float score = 0.0;
        std::pair<int, int> location;
        std::vector<Node*> children;

    private:
    };
    typedef Node * node;

    node root;
    int learning_rate;

public:

    Graph(int, std::pair<int, int>); // Constructor
    ~Graph();

    void buildGraph_Astar(std::vector< std::pair<int, int> >);
    void generateChildren(std::vector< std::pair<int, int> >, node);
    int getDistance(std::pair<int, int>, std::pair<int, int>);
};


#endif //AGENTPROJECT_GRAPH_H
