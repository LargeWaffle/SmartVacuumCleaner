#include "Graph.h"
#include <cmath>
#include <iostream>

using namespace std;

Graph::Graph(int lr, pair<int, int> vacPos)
{
    learning_rate = lr;
    root = new Node(vacPos);
}

Graph::~Graph()
{

}

void Graph::buildGraph_Astar(vector< pair<int, int> > targets) {

    /*cout << "Initial targets :" << targets.size() << endl;
    for (auto & target : targets) {
        cout << target.first << ", " << target.second << endl;
    }*/
    generateChildren(targets, root);

}

void Graph::generateChildren (vector< pair<int, int> > targets, node src) {

    if (!targets.empty())
    {
        for (int i = 0; i< targets.size(); i++) {
            node newNode = new Node (targets[i]);

            newNode->cost = getDistance(src->location, targets[i]) + 1; // make function
            newNode->score = 0.0; // make function
			newNode->actionData = getCell(targets[i].first, targets[i].second)->hasJewel();

            src->children.push_back(newNode);

            vector< pair<int, int> > newTargets(targets);
            newTargets.erase(newTargets.cbegin()+i);

            generateChildren(newTargets, newNode);
        }
    }
}

int Graph::getDistance (pair<int, int> a, pair<int, int> b) {

    int diffX = abs(a.first - b.first);
    int diffY = abs(a.second - b.second);
    return diffX + diffY;
}

