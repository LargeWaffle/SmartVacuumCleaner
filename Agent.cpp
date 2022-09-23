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

		nbTargets = sens->dustyCells();  // Desires ? Functions returns number of steps to do

		Graph problem = Graph(LEARNING_RATE);
		problem.buildGraph(dustCoords);

		if (actionList.empty())
			actionList = getActions(problem, nbTargets);

		int targetX = actionList[0].first, targetY = actionList[0].second;

		eff->travel(targetX, targetY);

		if (sens->locateAgent().first == targetX && sens->locateAgent().second == targetY)
		{
			if (sens->isJewel())
				eff->pickupCell();
			else {
				eff->cleanCell();
				sens->removeDust();
			}

			actionList.erase(actionList.begin());
		}

        /*
         * // Choose an action
        int dustIndex = 0;

        for (int i = 0; i < LEARNING_RATE; i++) {
            // Do the action
            if (sens->locateAgent().first != dustCoords[dustIndex].first || sens->locateAgent().second != dustCoords[dustIndex].second)
            {
                eff->travel(dustCoords[dustIndex].first, dustCoords[dustIndex].second);
                cout << "Im going towards : " << dustCoords[dustIndex].first << dustCoords[dustIndex].second << endl;
            } else {
                if (sens->isJewel())
                    eff->pickupCell();
                else {
                    eff->cleanCell();
                    sens->removeDust();
                    dustIndex++;
                }
            }
            cout << *map << endl;
            map->go = true;
        }
        cout << "\nFinished my first learning rate\n" << endl;*/
	}
}

std::vector<std::pair<int, int> > Agent::getActions(Graph problem, int depth) {

	problem.IDFS();
	return std::vector<std::pair<int, int>>();
}
