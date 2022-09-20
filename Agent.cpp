#include "Agent.h"
#include <random>

using namespace std;

Agent ::Agent(Map *mp){

	map = mp;
	map->getCell(rand() % mp->getMapSize(), rand() % mp->getMapSize())->setVacuum(true);

	eff = new Effector(mp);
	sens = new Sensor(mp);

	destX = rand() % mp->getMapSize();
	destY = rand() % mp->getMapSize();
}

Agent::~Agent() {

}

void Agent::agentWork() {

    // while
    // -- Sens environement
    // -- Update state
    // -- Choose action
    // -- Do it


	while (true) {
        // Observe the environment
        sens->retrieveDirtCoords();

        // Update state
        vector< pair<int, int> > dirtTab = sens->getDirtCoords();

        // Choose an action
        int dirtIndex = 0;

        for (int i = 0; i < LEARNING_RATE; i++) {
            // Do the action
            if (sens->locate().first != dirtTab[dirtIndex].first || sens->locate().second != dirtTab[dirtIndex].second)
            {
                eff->travel(dirtTab[dirtIndex].first, dirtTab[dirtIndex].second);
                cout << "Im going towards : " << dirtTab[dirtIndex].first << dirtTab[dirtIndex].second << endl;
            } else {
                if (sens->isJewel())
                    eff->pickupCell();
                else {
                    eff->cleanCell();
                    sens->removedDirt();
                    dirtIndex++;
                }
            }
            cout << *map << endl;
            map->go = true;
        }
        cout << "\nFinished my first learning rate\n" << endl;
	}
}
