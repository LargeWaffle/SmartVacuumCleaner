#include "Graph.h"
#include <cmath>
#include <algorithm>

using namespace std;

Graph::Graph(int lr, pair<int, int> vacPos, bool algo, Map* mp) {
    learning_rate = lr;
    root = new Node(vacPos);
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

vector<Graph::node> Graph::BFS() {

    vector<node> visited;
    queue<node> qu;

    qu.push(root);

    while (!qu.empty()) {
        node node = qu.front();
        qu.pop();

        if (map->getCell(node->location.first, node->location.second)->hasDust()) {

            vector<Graph::node> solution;
            while (node->parent != nullptr) {
                solution.push_back(node);
                node = node->parent;
            }
            return solution;

        } else {
            visited.push_back(node);
            expandNode( node, visited, &qu);
        }
    }
}

vector<Graph::node> Graph::Astar(int nbtargets) {
    vector<node> opened;
    vector<node> closed;

    root->nbtargs = nbtargets;
    opened.push_back(root);

    while (!opened.empty()) {
        sort(opened.begin(), opened.end());

        node q = opened.front();

        if (q->nbtargs == 0) { // we are in a solution node
            vector<node> solution;

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
                child->h =

                child->f = child->g + child->h;
            }

            if (betterNode(child, opened))
                continue;

            if (betterNode(child, closed))
                continue;
            else
                opened.push_back(getBetterNode(child, closed));
        }

        closed.push_back(q);

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

void Graph::buildNode(pair<int, int> loc, node parentNode, vector<Graph::node> &opened, queue<Graph::node> *queue) {

    node newNode = new Node(loc);

    bool dust_cond = map->getCell(loc.first, loc.second)->hasDust();

    newNode->actionData = dust_cond;
    if (dust_cond && newNode->nbtargs > 0)
        newNode->nbtargs -= 1;

    if (!newNode->actionData)
        newNode->actionData = map->getCell(loc.first, loc.second)->hasJewel();

    parentNode->children.push_back(newNode);
    newNode->parent = parentNode;

    if (algorithm)
        opened.push_back(newNode);
    else
        queue->push(newNode);
}
