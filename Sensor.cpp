#include "Sensor.h"
#include "Map.h"
#include <vector>

using namespace std;

Sensor::Sensor(Map *mp) {
	map = mp;
}

Sensor::~Sensor() {

}

void Sensor::getDirtCoords() {
	for (int i = 0; i < map->getMapSize(); i++)
		for (int j = 0; j < map->getMapSize(); j++)
		{
			if (map->getCell(map->getVacuum().first, map->getVacuum().second)->hasDirt())
				dirtCoords.emplace_back(i, j);

		}
}

bool Sensor::isJewel() {
	return map->getCell(map->getVacuum().first, map->getVacuum().second)->hasJewel();
}
