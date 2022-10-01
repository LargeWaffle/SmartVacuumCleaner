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

bool Sensor::isJewel(int x, int y) {
	return map->getCell(x, y)->hasJewel();
}

bool Sensor::isDust(int x, int y) {
	return map->getCell(x, y)->hasDust();
}

pair<int, int> Sensor::locateAgent() {
	return map->getVacuum();
}
