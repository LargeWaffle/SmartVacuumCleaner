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

void Agent::doOneMove() {

	while (true) {
		if(destX == sens->locate().first && destY == sens->locate().second)
		{
			destX = rand() % map->getMapSize();
			destY = rand() % map->getMapSize();
		}
		else
		{
			eff->travel(destX, destY);
		}
		cout << *map << endl;
        map->go = true;
	}
}