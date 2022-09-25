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

void Graph::buildGraph(vector< pair<int, int> > targets) {

    cout << "Initial targets :" << targets.size() << endl;
    for (int i = 0; i< targets.size(); i++) {
        cout << targets[i].first << ", " << targets[i].second << endl;
    }
    generateChildren(targets, root);

}

void Graph::generateChildren (vector< pair<int, int> > targets, node src) {

    if (!targets.empty())
    {
        for (int i = 0; i< targets.size(); i++) {
            node newNode = new Node (targets[i]);
            newNode->score = 0; // make function
            newNode->cost = getDistance(src->location, targets[i]) + 1; // make function

            src->children.push_back(newNode);
            vector< pair<int, int> > newTargets(targets);
            newTargets.erase(newTargets.cbegin()+i);

            cout << "im node " << newNode->location.first << ", " << newNode->location.second << endl;
            generateChildren(newTargets, newNode);
        }
    }
}

int Graph::getDistance (pair<int, int> a, pair<int, int> b) {
    int diffX = abs(a.first - b.first);
    int diffY = abs(a.second - b.second);
    return diffX + diffY;
}
/*
vector< pair<int, int> > Graph::UCS(int goal, int start) {

}*/
