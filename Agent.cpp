#include "Agent.h"
#include <random>

Agent ::Agent(Map *mp){
	coordX = rand() % mp->getMapSize();
	coordY = rand() % mp->getMapSize();

	map = mp;
	map->getCell(coordX, coordY)->setVacuum(true);

	eff = new Effector(mp);
	sens = new Sensor(mp);
}

Agent::~Agent() {

}

int Agent::getX() {
	return coordX;
}

int Agent::getY() {
	return coordY;
}