#include "Graph.h"
#include <cmath>
#include <algorithm>

using namespace std;

Graph::Graph(int lr, pair<int, int> vacPos, bool algo, Map *mp) {
	learning_rate = lr;
	//root = new Node(vacPos);
	algorithm = algo;
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
		node node = qu.front();
		qu.pop();

		if (map->getCell(node->location.first, node->location.second)->hasDust()) {
			node->actionData = true; // hotfix

			if (node == root) {
				solution.push_back(node);
				return solution;
			}

			do {
				solution.push_back(node);
				node = node->parent;
			} while (node != nullptr);

			return solution;

		} else {
			visited.push_back(node);
			expandBFSNode(node, visited, &qu);
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

	opened.push_back(root);

	while (!opened.empty()) {
		int index = 0, i = 0;
		node q = opened[0];
		for (auto elem: opened) {
			if (elem->f < q->f) {
				q = elem;
				index = i;
			}
			i++;
		}

		opened.erase(opened.begin() + index);
		closed.push_back(q);

		if (map->getCell(q->location.first, q->location.second)->hasDust()) { // we are in a solution node

			q->actionData = true; // hotfix

			if (q == root) {
				solution.push_back(q);
				return solution;
			}

			do {
				solution.push_back(q);
				q = q->parent;
			} while (q->parent != nullptr);

			return solution;
		}

		expandAStarNode(q, opened, closed);

		for (auto child: q->children) {

			child->g = q->g + getDistance(child->location, q->location);
			child->h = getAreaScore(q->location);
			child->f = child->g + child->h;

			if (betterNode(child, opened))
				continue;

			opened.push_back(child);
		}

	}

	solution.push_back(root);
	return solution;
}

void Graph::expandAStarNode(node node, vector<Graph::node> &opened, vector<Graph::node> &closed) {

	int x = node->location.first, y = node->location.second;

	if (x > 0 && isNodeUnvisited(make_pair(x - 1, y), closed))
		buildAStarNode(make_pair(x - 1, y), node, opened, closed);

	if (x < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(x + 1, y), closed))
		buildAStarNode(make_pair(x + 1, y), node, opened, closed);

	if (y > 0 && isNodeUnvisited(make_pair(x, y - 1), closed))
		buildAStarNode(make_pair(x, y - 1), node, opened, closed);

	if (y < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(x, y + 1), closed))
		buildAStarNode(make_pair(x, y + 1), node, opened, closed);

}

void Graph::expandBFSNode(node node, vector<Graph::node> &opened, queue<Graph::node> *queue) {

	int x = node->location.first, y = node->location.second;

	if (x > 0 && isNodeUnvisited(make_pair(x - 1, y), opened))
		buildBFSNode(make_pair(x - 1, y), node, opened, queue);

	if (x < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(x + 1, y), opened))
		buildBFSNode(make_pair(x + 1, y), node, opened, queue);

	if (y > 0 && isNodeUnvisited(make_pair(x, y - 1), opened))
		buildBFSNode(make_pair(x, y - 1), node, opened, queue);

	if (y < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(x, y + 1), opened))
		buildBFSNode(make_pair(x, y + 1), node, opened, queue);

}

void
Graph::buildAStarNode(pair<int, int> loc, node parentNode, vector<Graph::node> &opened, vector<Graph::node> &closed) {

	node newNode = new Node(loc);
	parentNode->children.push_back(newNode);
	newNode->parent = parentNode;
}

void Graph::buildBFSNode(pair<int, int> loc, node parentNode, vector<Graph::node> &opened, queue<Graph::node> *queue) {

	node newNode = new Node(loc);

	newNode->actionData = map->getCell(loc.first, loc.second)->hasDust();

	if (!newNode->actionData)
		newNode->actionData = map->getCell(loc.first, loc.second)->hasJewel();

	parentNode->children.push_back(newNode);
	newNode->parent = parentNode;

	queue->push(newNode);
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

Graph::node Graph::getBetterNode(node child, vector<Graph::node> &list) {

	for (auto elem: list)
		if (elem->location == child->location && elem->g < child->g)
			return elem;

	return nullptr;
}

int Graph::getAreaScore(pair<int, int> loc) {
	int score = 0;

	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
				if (map->getCell(i,j)->hasDust())
					if (getDistance(loc, make_pair(i,j)) < MAP_SIZE)
						score += (getDistance(loc, make_pair(i,j)) - MAP_SIZE);

	return score;
}