#include "Sensor.h"
#include "Map.h"

#include <vector>
using namespace std;

void Sensor::getDirtCoords() {
	for (int i = 0; i < getMapSize(); i++)
		for (int j = 0; j < getMapSize(); j++)
		{
			if (map[i][j].hasDirt())
				dirtCoords.push_back(make_pair(i, j));

		}
}

bool Sensor::isJewelInDirt() {
	return map[coordX][coordY].hasJewel();
}