#include "Sensor.h"
#include "Map.h"
#include <vector>

using namespace std;

Sensor::Sensor(Map *mp) {
	map = mp;
}

Sensor::~Sensor() {

}

std::vector<std::pair<int, int>> Sensor::getDustCoords() {
	dustCoords.clear();

	for (int i = 0; i < map->getMapSize(); i++)
		for (int j = 0; j < map->getMapSize(); j++)
		{
			if (map->getCell(i, j)->hasDust())
				dustCoords.emplace_back(i, j);
		}

    return dustCoords;
}

void Sensor :: removeDust() {
    dustCoords.erase(dustCoords.begin());
}

bool Sensor::isJewel() {
	return map->getCell(map->getVacuum().first, map->getVacuum().second)->hasJewel();
}

pair<int, int> Sensor::locateAgent() {
	return map->getVacuum();
}

int Sensor::dustyCells() {
    dustCoords.size();
}
