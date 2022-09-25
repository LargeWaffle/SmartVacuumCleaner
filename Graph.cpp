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

    //cout << "Initial targets :" << targets.size() << endl;
    for (auto & target : targets) {
        cout << target.first << ", " << target.second << endl;
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

pair<bool, pair<int, int>> Graph::BFS() {

	vector<pair<int, int>> visited;
	queue<pair<int, int> > qu;

	qu.push(sens->locateAgent());

	while (!qu.empty()) {
		pair<int, int> node = qu.front();
		qu.pop();

		if (sens->isDust(node.first, node.second)) {

			pair<bool, pair<int, int>> action = make_pair(false, node);

			if (sens->isJewel(node.first, node.second))
				action.first = true;

			return action;
		} else {
			visited.push_back(node);
			expandNode(node, qu, visited);
		}
	}
	return make_pair(0, sens->locateAgent());
}

void Graph::expandNode(pair<int, int> pos, queue<pair<int, int>> &nodeList, vector<pair<int, int>> &visited) {

	if (pos.first > 0 && isNodeUnvisited(make_pair(pos.first - 1, pos.second), visited))
		nodeList.push(make_pair(pos.first - 1, pos.second));

	if (pos.first < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(pos.first + 1, pos.second), visited))
		nodeList.push(make_pair(pos.first + 1, pos.second));

	if (pos.second > 0 && isNodeUnvisited(make_pair(pos.first, pos.second - 1), visited))
		nodeList.push(make_pair(pos.first, pos.second - 1));

	if (pos.second < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(pos.first, pos.second + 1), visited))
		nodeList.push(make_pair(pos.first, pos.second + 1));
}

bool Graph::isNodeUnvisited(pair<int, int> pos, vector<pair<int, int>> &visited) {

	for (auto elem: visited)
		if (elem == pos)
			return false;

	return true;
}

