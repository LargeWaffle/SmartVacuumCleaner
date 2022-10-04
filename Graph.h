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
        explicit Node(std::pair<int, int> data, int targs = -1, const std::vector<Node*>& child_list = {})
                : location(std::move(data)){};

        int cost = 1;
        int actionData = 0;
        std::vector<std::pair<int, int>> targets;
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

    Map * map;

public:
    typedef Node * node;

    explicit Graph(Map*); // Constructor
    ~Graph();

	std::vector<node> Astar(std::pair<int, int>);
    std::vector<node> BFS (std::pair<int, int>);

    int getDistance(std::pair<int, int>, std::pair<int, int>);

    void expandNode(node, std::vector<node>&);

    bool isNodeUnvisited(std::pair<int, int>, std::vector<node>&);

	void buildNode(std::pair<int, int>, node);

	std::vector<std::vector<int>> generateScores(int&);

	bool betterNode(node, std::vector<node> &);
	int cellScore(std::pair<int, int> loc);

    // Fonctions de la deuxième version du A*

    std::vector<node> AstarTwo(std::pair<int, int>, std::vector<std::pair<int, int>>);
    void expandNodeTwo(node, std::vector<node>&);
    bool isNodeUnvisitedTwo(std::pair<int, int>, std::vector<node>&, node);
    bool betterNodeTwo(node, std::vector<node> &);
    int getClosestDust(std::pair<int, int>, std::vector<std::pair<int, int>>);
};


#endif //AGENTPROJECT_GRAPH_H
