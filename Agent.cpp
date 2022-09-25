#include "Agent.h"
#include <random>

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

        vector< pair<int, int> > dustCoords = sens->getDustCoords();    // Observe & update state

        nbTargets = sens->dustyCells();  // Desires ? Function returns number of steps to take
        pair<int, int> initialVacPos = sens->locateAgent();

        Graph problem = Graph(LEARNING_RATE, initialVacPos);
        problem.buildGraph(dustCoords);

        cout << "hello"  << endl;

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
	}
}

std::vector<std::pair<int, int> > Agent::getActions(Graph problem, int depth) {

	problem.IDFS();
	return std::vector<std::pair<int, int>>();
}
