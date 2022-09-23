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
        sens->retrieveDustCoords();

        // Update state
        vector< pair<int, int> > dustCoords = sens->getDustCoords();

        // Choose an action
        int dustIndex = 0;

        for (int i = 0; i < LEARNING_RATE; i++) {
            // Do the action
            if (sens->locate().first != dustCoords[dustIndex].first || sens->locate().second != dustCoords[dustIndex].second)
            {
                eff->travel(dustCoords[dustIndex].first, dustCoords[dustIndex].second);
                cout << "Im going towards : " << dustCoords[dustIndex].first << dustCoords[dustIndex].second << endl;
            } else {
                if (sens->isJewel())
                    eff->pickupCell();
                else {
                    eff->cleanCell();
                    sens->removedDust();
                    dustIndex++;
                }
            }
            cout << *map << endl;
            map->go = true;
        }
        cout << "\nFinished my first learning rate\n" << endl;
	}
}
