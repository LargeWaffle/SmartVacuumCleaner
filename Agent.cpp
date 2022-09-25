#include "Agent.h"
#include <random>
#include <queue>

using namespace std;

Agent::Agent(Map *mp, bool smart) {

	map = mp;
	smartAgent = smart;

	int coordX = rand() % mp->getMapSize();
	int coordY = rand() % mp->getMapSize();

	map->getCell(coordX, coordY)->setVacuum(true);

	eff = new Effector(mp);
	sens = new Sensor(mp);

	nbTargets = 0;
	actionList = {};
}

Agent::~Agent() {

	delete eff;
	delete sens;

}

void Agent::agentWork() {

	while (true) {

		pair<int, int> agentLocation = sens->locateAgent();
		Graph problem = Graph(LEARNING_RATE, agentLocation);

		if (smartAgent) {

			vector<pair<int, int> > dustCoords = sens->getDustCoords();    // Observe & update state
			nbTargets = sens->dustyCells();  // Desires ? Function returns number of steps to take

			for (int i = 0; i < LEARNING_RATE; i++) {

				if (actionList.empty())
					getActions(problem, nbTargets);
				else {
					bool targetAction = actionList[0].first;
					pair<int, int> targetLocation = actionList[1].second;

					if (agentLocation == targetLocation) {
						eff->actOnCell(targetAction);
						actionList.erase(actionList.begin());
					} else
						eff->travel(targetLocation.first, targetLocation.second);
				}
			}

		} else {

			pair<bool, pair<int, int>> target = BFS();

			bool targetAction = target.first;
			pair<int, int> targetLocation = target.second;

			eff->travel(targetLocation.first, targetLocation.second);

			if (agentLocation == targetLocation)
				eff->actOnCell(targetAction);

			cout << *map << endl;
		}
	}
}

void Agent::getActions(Graph problem, int nb){

	actionList = problem.Astar();
}

pair<bool, pair<int, int>> Agent::BFS() {

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

void Agent::expandNode(pair<int, int> pos, queue<pair<int, int>> &nodeList, vector<pair<int, int>> &visited) {

	if (pos.first > 0 && isNodeUnvisited(make_pair(pos.first - 1, pos.second), visited))
		nodeList.push(make_pair(pos.first - 1, pos.second));

	if (pos.first < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(pos.first + 1, pos.second), visited))
		nodeList.push(make_pair(pos.first + 1, pos.second));

	if (pos.second > 0 && isNodeUnvisited(make_pair(pos.first, pos.second - 1), visited))
		nodeList.push(make_pair(pos.first, pos.second - 1));

	if (pos.second < (MAP_SIZE - 1) && isNodeUnvisited(make_pair(pos.first, pos.second + 1), visited))
		nodeList.push(make_pair(pos.first, pos.second + 1));
}

bool Agent::isNodeUnvisited(pair<int, int> pos, vector<pair<int, int>> &visited) {

	for (auto elem: visited)
		if (elem == pos)
			return false;

	return true;
}