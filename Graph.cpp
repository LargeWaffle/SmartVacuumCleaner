#include "Graph.h"
#include <cmath>
#include <algorithm>

using namespace std;

Graph::Graph(Map *mp) {
	map = mp;
}

Graph::~Graph() {

}

int Graph::getDistance(pair<int, int> a, pair<int, int> b) {

	int diffX = abs(a.first - b.first);
	int diffY = abs(a.second - b.second);
	return diffX + diffY;
}

vector<Graph::node> Graph::BFS(pair<int, int> vacPos) {

	node root = new Node(vacPos);
	vector<node> visited;
	vector<node> solution;
	queue<node> qu;

	qu.push(root);

	while (!qu.empty()) {
		node current = qu.front();
		qu.pop();

		if (map->getCell(current->location.first, current->location.second)->hasDust()) {

			if (current == root) {
                current->actionData = 2; // hotfix
				solution.push_back(current);
				return solution;
			}

			do {
				solution.push_back(current);
                current = current->parent;
			} while (current->parent != nullptr);

			return solution;

		} else {
			visited.push_back(current);
			expandNode(current, visited);

            for (auto child: current->children)
                qu.push(child);
		}
	}

	solution.push_back(root);
	return solution;
}

vector<Graph::node> Graph::Astar(pair<int, int> vacPos) {

	vector<node> opened;
	vector<node> closed;
	vector<node> solution;
	node root = new Node(vacPos);

	int maxScore = 0;
	vector<vector<int>> scoreTab = generateScores(maxScore);
	opened.push_back(root);

	while (!opened.empty()) {
		int index = 0, i = 0;
		node current = opened[0];
		for (auto elem: opened) {
			if (elem->f < current->f) {
                current = elem;
				index = i;
			}
			i++;
		}

		opened.erase(opened.begin() + index);
		closed.push_back(current);

		if (map->getCell(current->location.first, current->location.second)->hasDust()) { // we are in a solution node

            if (current == root) {
                if (map->getCell(current->location.first, current->location.second)->hasJewel() && map->getCell(current->location.first, current->location.second)->hasDust())
                    current->actionData = 3;
                else if (map->getCell(current->location.first, current->location.second)->hasDust())
                    current->actionData = 2;
                else if (map->getCell(current->location.first, current->location.second)->hasJewel())
                    current->actionData = 1;
                solution.push_back(current);
				return solution;
			}

			do {
				solution.push_back(current);
                current = current->parent;
			} while (current->parent != nullptr);

			return solution;
		}

		expandNode(current, closed);

		for (auto child: current->children) {

			child->g = current->g + getDistance(child->location, current->location);

			child->h = maxScore - scoreTab[child->location.first][child->location.second];

			child->f = child->g + child->h;

			if (betterNode(child, opened))
				continue;

			opened.push_back(child);
		}

	}

	solution.push_back(root);
	return solution;
}

void Graph::expandNode(node node, vector<Graph::node> &closed) {

	int x = node->location.first, y = node->location.second;

	if (x > 0 && isNodeUnvisited(make_pair(x - 1, y), closed))
		buildNode(make_pair(x - 1, y), node);

	if (x < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(x + 1, y), closed))
		buildNode(make_pair(x + 1, y), node);

	if (y > 0 && isNodeUnvisited(make_pair(x, y - 1), closed))
		buildNode(make_pair(x, y - 1), node);

	if (y < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(x, y + 1), closed))
		buildNode(make_pair(x, y + 1), node);

}


void Graph::buildNode(pair<int, int> loc, node parentNode) {

	node newNode = new Node(loc);

    if (map->getCell(loc.first, loc.second)->hasJewel() && map->getCell(loc.first, loc.second)->hasDust())
        newNode->actionData = 3;
    else if (map->getCell(loc.first, loc.second)->hasDust())
        newNode->actionData = 2;
    else if (map->getCell(loc.first, loc.second)->hasJewel())
        newNode->actionData = 1;

	parentNode->children.push_back(newNode);
	newNode->parent = parentNode;
}

bool Graph::isNodeUnvisited(pair<int, int> pos, vector<Graph::node> &list) {

	for (auto elem: list)
		if (elem->location == pos)
			return false;

	return true;
}

bool Graph::betterNode(node child, vector<Graph::node> &list) {

	for (auto elem: list)
		if (elem->location == child->location && elem->g < child->g)
			return true;

	return false;
}

vector<vector<int>> Graph::generateScores(int &maxScore) {

	vector<vector<int>> tab(MAP_SIZE, vector<int>(MAP_SIZE));

	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++) {
			tab[i][j] = cellScore(make_pair(i,j));
			if (tab[i][j] > maxScore)
				maxScore = tab[i][j];
		}

	return tab;
}

int Graph::cellScore(pair<int, int> loc) {
	int score = 0;

	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
			if (getDistance(loc, make_pair(i,j)) < 3)
				if (map->getCell(i,j)->hasDust())
					score += 1;

	return score;
}