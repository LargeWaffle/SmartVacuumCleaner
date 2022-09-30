#include "Effector.h"
#include "Map.h"
#include <cmath>

using namespace std;

Effector::Effector(Map *mp) {
	map = mp;
}

Effector::~Effector() {

}

int Effector::actOnCell(int targetAction, int actionCredit) {
	int res = 0;

	if (targetAction == 1 && actionCredit >= 1) {
		map->pickup();
		res = 1;
	} else if (targetAction == 2 && actionCredit >= 1) {
		map->clean();
		res = 1;
	} else if (targetAction == 3) {

		if (actionCredit >= 1) {
			map->pickup();
			res += 1;
			actionCredit--;
		}

		if (actionCredit >= 1) {
			map->clean();
			res += 1;
		}
	}
	return res;
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


