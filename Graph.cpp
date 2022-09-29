#include "Graph.h"
#include <cmath>
#include <algorithm>

using namespace std;

Graph::Graph(int lr, pair<int, int> vacPos, bool algo, Map* mp) {
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

            do {
                solution.push_back(node);
                node = node->parent;
            } while (node != nullptr);

            return solution;

        } else {
            visited.push_back(node);
            expandNode(node, visited, &qu);
        }
    }

    solution.push_back(root);
	return solution;
}

vector<Graph::node> Graph::Astar(pair<int, int> vacPos, int nbtargets) {
    vector<node> opened;
    vector<node> closed;
	vector<node> solution;
    node root = new Node(vacPos);

	if (nbtargets != 0)
	{
		root->nbtargs = nbtargets;
		opened.push_back(root);

		while (!opened.empty()) {
			sort(opened.begin(), opened.end());

			node q = opened.front();

			if (q->nbtargs == 0) { // we are in a solution node

				while (q->parent != nullptr) {
					solution.push_back(q);
					q = q->parent;
				}
				return solution;
			}

			opened.erase(opened.begin());

			expandNode( q, opened);

			for (auto child: q->children) {

				if (child->nbtargs == 0)
					continue;
				else {
					child->g = q->g + getDistance(child->location, q->location);
					child->h = abs(root->nbtargs - child->nbtargs);
					child->f = child->g + child->h;
				}

				if (betterNode(child, opened))
					continue;

				if (betterNode(child, closed))
					continue;
				else if(getBetterNode(child, closed) != nullptr)
					opened.push_back(getBetterNode(child, closed));
			}

			closed.push_back(q);

		}
	}else{
		solution.push_back(root);
		return solution;
	}
}

void Graph::expandNode(node node, vector<Graph::node> &opened, queue<Graph::node> *queue) {

    int x = node->location.first, y = node->location.second;

    if (x > 0 && isNodeUnvisited(make_pair(x - 1, y), opened))
        buildNode(make_pair(x - 1, y), node, opened, queue);

    if (x < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(x + 1, y), opened))
        buildNode(make_pair(x + 1, y), node, opened, queue);

    if (y > 0 && isNodeUnvisited(make_pair(x, y - 1), opened))
        buildNode(make_pair(x, y - 1), node, opened, queue);

    if (y < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(x, y + 1), opened))
        buildNode(make_pair(x, y + 1), node, opened, queue);

}

void Graph::buildNode(pair<int, int> loc, node parentNode, vector<Graph::node> &opened, queue<Graph::node> *queue) {

    node newNode = new Node(loc);

    newNode->actionData = map->getCell(loc.first, loc.second)->hasDust();

    if (parentNode->nbtargs > 0 && algorithm)
        newNode->nbtargs = parentNode->nbtargs - newNode->actionData;

    if (!newNode->actionData)
        newNode->actionData = map->getCell(loc.first, loc.second)->hasJewel();

    parentNode->children.push_back(newNode);
    newNode->parent = parentNode;

    if (algorithm)
        opened.push_back(newNode);
    else
        queue->push(newNode);
}


bool Graph::isNodeUnvisited(pair<int, int> pos, vector<Graph::node> &opened) {

    for (auto elem: opened)
        if (elem->location == pos)
            return false;

    return true;
}

bool Graph::betterNode(node child, vector<Graph::node> &list) {

    for (auto elem: list)
        if (elem->location == child->location && elem->f < child->f)
            return true;

    return false;
}

Graph::node Graph::getBetterNode(node child, vector<Graph::node> &list) {

    for (auto elem: list)
        if (elem->location == child->location && elem->f < child->f)
            return elem;

    return nullptr;
}

