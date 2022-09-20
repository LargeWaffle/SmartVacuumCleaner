#ifndef AGENTPROJECT_SENSOR_H
#define AGENTPROJECT_SENSOR_H

#include "Map.h"
#include <vector>

class Sensor {
public:

	Sensor(Map*);
	~Sensor();

	void retrieveDirtCoords();
	bool isJewel();
	std::pair<int, int> locate();
    std::vector<std::pair<int, int>> getDirtCoords();
    void removedDirt();
    int dustyCells();

private:
	Map* map;
	std::vector<std::pair<int, int>> dirtCoords;

};

#endif //AGENTPROJECT_SENSOR_H
