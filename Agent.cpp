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

    pair<int, int> agentLocation = sens->locateAgent();
    problem = new Graph(LEARNING_RATE, agentLocation, smartAgent, map);


	while (true) {

        //for (int i = 0; i < LEARNING_RATE; i++) {

        if (actionList.empty())
            actionList = getActions();

        bool targetAction = actionList.front()->actionData;
        pair<int, int> targetLocation = actionList.front()->location;

        if (agentLocation != targetLocation)
            eff->travel(targetLocation.first, targetLocation.second);

        eff->actOnCell(targetAction);

        actionList.erase(actionList.begin());

        cout << *map << endl;
	}
}

vector<Graph::node> Agent::getActions(){

	nbTargets = sens->dustyCells();  // Desires ? Function returns number of steps to take

	actionList = problem.Astar(dustCoords);
}
