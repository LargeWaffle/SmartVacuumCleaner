#include "Agent.h"
#include <random>
#include <queue>

using namespace std;

Agent ::Agent(Map *mp){

	map = mp;
	map->getCell(rand() % mp->getMapSize(), rand() % mp->getMapSize())->setVacuum(true);

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

	// while
	// -- Sens environement
	// -- Update state
	// -- Choose action
	// -- Do it

	while (true) {
		if (smartAgent) {
			vector<pair<int, int> > dustCoords = sens->getDustCoords();    // Observe & update state

			nbTargets = sens->dustyCells();  // Desires ? Function returns number of steps to take
			pair<int, int> initialVacPos = sens->locateAgent();

			Graph problem = Graph(LEARNING_RATE, initialVacPos);
			problem.buildGraph(dustCoords);

			/*for (int i = 0; i < LEARNING_RATE; i++) {
            if (actionList.empty())
                actionList = getActions(problem, nbTargets);
            else {
                int targetX = actionList[0].first, targetY = actionList[0].second;

                if (sens->locateAgent().first == targetX && sens->locateAgent().second == targetY) {
                    if (sens->isJewel())
                        eff->pickupCell();
                    else {
                        eff->cleanCell();
                        sens->removeDust();
                    }
                    actionList.erase(actionList.begin());
                }
                else
                    eff->travel(targetX, targetY);
            }
        }*/

		} else {
			pair<bool, pair<int, int>> target = BFS();

			bool targetAction = target.first;
			pair<int, int> targetLocation = target.second;

			eff->travel(targetLocation.first, targetLocation.second);

			if (sens->locateAgent().first == targetLocation.first &&
			    sens->locateAgent().second == targetLocation.second)
				eff->actOnCell(targetAction);

			cout << *map << endl;
		}
	}
}

pair<bool, pair<int, int>> Agent::BFS(){

	vector<pair<int, int>> visited;
	queue< pair<int, int> > qu;

	qu.push(sens->locateAgent());

	while(!qu.empty())
	{
		pair<int, int> node = qu.front();
		qu.pop();

		if (sens->isDust(node.first, node.second)){

			pair<bool, pair<int, int>> action = make_pair(0, node);

			if (sens->isJewel(node.first, node.second))
				action.first = 1;

			return action;
		}
		else {
			visited.push_back(node);
			expandNode(node, qu, visited);
		}
	}
	return make_pair(0, sens->locateAgent());
}

void Agent::expandNode(pair<int, int> pos, queue< pair<int, int>>& nodeList, vector< pair<int, int>>& visited) {

	if (pos.first > 0 && isNodeUnvisited(make_pair(pos.first-1, pos.second), visited))
		nodeList.push(make_pair(pos.first-1, pos.second));

	if (pos.first < (MAP_SIZE-1) && isNodeUnvisited(make_pair(pos.first+1, pos.second), visited))
		nodeList.push(make_pair(pos.first+1, pos.second));

	if (pos.second > 0 && isNodeUnvisited(make_pair(pos.first, pos.second-1), visited))
		nodeList.push(make_pair(pos.first, pos.second-1));

	if (pos.second < (MAP_SIZE-1) && isNodeUnvisited(make_pair(pos.first, pos.second+1), visited))
		nodeList.push(make_pair(pos.first, pos.second+1));

}

bool Agent::isNodeUnvisited(pair<int, int> pos, vector< pair<int, int>>& visited) {

	for (auto elem: visited)
		if (elem == pos)
			return false;

	return true;
}