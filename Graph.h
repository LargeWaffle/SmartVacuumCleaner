#ifndef AGENTPROJECT_GRAPH_H
#define AGENTPROJECT_GRAPH_H

#include <utility>
#include <vector>
#include <queue>
#include "Map.h"

class Graph {
private:
    class Node{
    public:
        Node(std::pair<int, int> data, int targs = -1, std::vector<Node*> child_list = {})
                : location(std::move(data)), nbtargs(targs) {};

        int cost = 1;
        bool actionData = false;
        int nbtargs;
        Node* parent = nullptr;

        int g = 0;
        int h = 0;
        int f = 0;

		std::pair<int, int> location;
        std::vector<Node*> children;

        bool operator<(const Node& nd) const{
            return cost < nd.cost;
        };
    };

    int learning_rate;
    bool algorithm;
    Map * map;

public:
    typedef Node * node;
    node root;

    Graph(int, std::pair<int, int>, bool, Map*); // Constructor
    ~Graph();

	std::vector<node> Astar(int);
    std::vector<node> BFS ();

    int getDistance(std::pair<int, int>, std::pair<int, int>);

    //void expandBFSNode(std::pair<int, int> pos, std::queue< std::pair<int, int>>&, std::vector< std::pair<int, int>>&);
    void expandNode(node, std::vector<node>&, std::queue<node>* = new std::queue<node> ());

    bool isNodeUnvisited(std::pair<int, int>, std::vector<node>&);
    void buildNode(std::pair<int, int>, node, std::vector<node>&, std::queue<node>* = new std::queue<node> ());

    bool betterNode(node, std::vector<node> &);
    node getBetterNode(node, std::vector<node> &);
};


#endif //AGENTPROJECT_GRAPH_H
