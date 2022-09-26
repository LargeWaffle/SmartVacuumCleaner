#include "Graph.h"
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

Graph::Graph(int lr, pair<int, int> vacPos)
{
    learning_rate = lr;
    root = new Node(vacPos);
}

Graph::~Graph()
{

}

void Graph::generateChildren (Agent *agent, vector< pair<int, int> > targets, node src) {

    if (!targets.empty())
    {
        for (int i = 0; i< targets.size(); i++) {
            node newNode = new Node (targets[i]);

			newNode->actionData = agent->sens->isJewel(targets[i].first, targets[i].second);
            newNode->cost = getDistance(src->location, targets[i]) + 1 + newNode->actionData;

            src->children.push_back(newNode);

            vector< pair<int, int> > newTargets(targets);
            newTargets.erase(newTargets.cbegin()+i);

            generateChildren(agent, newTargets, newNode);
        }
    }
}

int Graph::getDistance (pair<int, int> a, pair<int, int> b) {

    int diffX = abs(a.first - b.first);
    int diffY = abs(a.second - b.second);
    return diffX + diffY;
}

std::vector<std::pair<bool, std::pair<int, int>>> Graph::Astar(vector< pair<int, int> >) {
    vector<node> opened;
    vector<node> closed;

    opened.push_back(root);

    while(!opened.empty()){
        sort(opened.begin(), opened.end());

        node q =
    }

	return ;
}


