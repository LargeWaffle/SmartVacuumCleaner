#ifndef AGENTPROJECT_GRAPH_H
#define AGENTPROJECT_GRAPH_H

#include <utility>
#include <vector>
#include "Agent.h"

class Graph {
private:
    class Node{
    public:
        Node(std::pair<int, int> data, std::vector<Node*> child_list = {})
                : location(std::move(data)){};

        int cost = 1;
        bool actionData = false;

		std::pair<int, int> location;
        std::vector<Node*> children;

        bool operator<(const node& nd) const{
            return cost < nd->cost;
        };

    private:
    };
    typedef Node * node;

    node root;
    int learning_rate;

public:

    Graph(int, std::pair<int, int>); // Constructor
    ~Graph();

	std::vector<std::pair<bool, std::pair<int, int>>> Astar(std::vector< std::pair<int, int> >);
    void generateChildren(Agent*, std::vector< std::pair<int, int> >, node);
    int getDistance(std::pair<int, int>, std::pair<int, int>);

};


#endif //AGENTPROJECT_GRAPH_H
