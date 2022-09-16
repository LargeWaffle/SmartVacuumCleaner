#include "Effector.h"
#include <math.h>

void Effector::cleanCell() {
	map[coordX][coordY].hasDirt = false;
}

void Effector::pickupCell() {
	map[coordX][coordY].hasJewel = false;
}

int Effector::travelCost(int destX, int destY) {
	int x = abs(coordX - destX);
	int y = abs(coordY - destY);
	return x + y;
}
