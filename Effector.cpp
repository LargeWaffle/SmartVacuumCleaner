#include "Effector.h"
#include "Map.h"
#include <cmath>

using namespace std;

Effector::Effector(Map *mp) {
	map = mp;
}

Effector::~Effector() {

}

void Effector::cleanCell() {
	map->clean();
}

void Effector::pickupCell() {
	map->pickup();
}

int Effector::travelCost(int destX, int destY) {
	int x = abs(map->getVacuum().first - destX);
	int y = abs(map->getVacuum().second - destY);
	return x + y;
}

void Effector::travel(int destX, int destY) {
	int coordX = map->getVacuum().first;
	int coordY = map->getVacuum().second;

	while (destX != coordX || destY != coordY) {
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


