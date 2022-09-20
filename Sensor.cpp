#include "Sensor.h"
#include "Map.h"
#include <vector>

using namespace std;

Sensor::Sensor(Map *mp) {
	map = mp;
}

Sensor::~Sensor() {

}

void Sensor::retrieveDirtCoords() {
	for (int i = 0; i < map->getMapSize(); i++)
		for (int j = 0; j < map->getMapSize(); j++)
		{
			if (map->getCell(i, j)->hasDirt())
				dirtCoords.emplace_back(i, j);
		}
}

std::vector<std::pair<int, int>> Sensor::getDirtCoords() {
    return dirtCoords;
}

void Sensor :: removedDirt() {
    dirtCoords.erase(dirtCoords.begin());
}

bool Sensor::isJewel() {
	return map->getCell(map->getVacuum().first, map->getVacuum().second)->hasJewel();
}

pair<int, int> Sensor::locate() {
	return map->getVacuum();
}

int Sensor::dustyCells() {
    dirtCoords.size();
}
