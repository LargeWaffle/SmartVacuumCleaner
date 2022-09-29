#include "Agent.h"

#include <random>

using namespace std;

Agent::Agent(Map *mp, bool smart) {

	map = mp;
	smartAgent = smart;

	int coordX = rand() % mp->getMapSize();
	int coordY = rand() % mp->getMapSize();

	map->getCell(coordX, coordY)->setVacuum(true);

	eff = new Effector(mp);
	sens = new Sensor(mp);

	nbtargets = 0;
	actionList = {};
}

Agent::~Agent() {

	delete eff;
	delete sens;

}

void Agent::agentWork() {

    problem = new Graph(LEARNING_RATE, sens->locateAgent(), smartAgent, map);

    int cpt = 0;
	while (true) {
        cpt++;

        //for (int i = 0; i < LEARNING_RATE; i++) {

        if (actionList.empty())
            actionList = getActions();

        if (actionList.empty())
            cout << "hello" << endl;

        bool targetAction = actionList.back()->actionData;
        pair<int, int> targetLocation = actionList.back()->location;

        if (sens->locateAgent() != targetLocation)
            eff->travel(targetLocation.first, targetLocation.second);

        eff->actOnCell(targetAction);

        actionList.pop_back();

        cout << *map << endl;
        cout << cpt << endl;
	}
}

vector<Graph::node> Agent::getActions(){

	nbtargets = sens->dustyCells();  // Desires ? Function returns number of steps to take

    if(smartAgent)
	    return problem->Astar(sens->locateAgent(), nbtargets);
    else
        return problem->BFS(sens->locateAgent());
}
