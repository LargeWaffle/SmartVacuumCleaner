#include "Effector.h"
#include "Map.h"
#include <cmath>

using namespace std;

Effector::Effector(Map *mp) {
	map = mp;
}

Effector::~Effector() {

}

void Effector::actOnCell(int targetAction) {
	if (targetAction == 1)
        map->pickup();
    else if (targetAction == 2)
        map->clean();
    else if (targetAction == 3) {
        map->pickup();
        map->clean();
    }
}

int Effector::travelCost(int destX, int destY) {
	int x = abs(map->getVacuum().first - destX);
	int y = abs(map->getVacuum().second - destY);
	return x + y;
}

void Effector::travel(int destX, int destY) {
	int coordX = map->getVacuum().first;
	int coordY = map->getVacuum().second;

	if (destX != coordX || destY != coordY) {
		map->getCell(coordX, coordY)->setVacuum(false);

		if (destX > coordX)
			coordX++;
		else if (destX < coordX)
			coordX--;
		else if (destY > coordY)
			coordY++;
		else if (destY < coordY)
			coordY--;

		map->getCell(coordX, coordY)->setVacuum(true);
	}

	// mesure de perf avec travelcost
}


