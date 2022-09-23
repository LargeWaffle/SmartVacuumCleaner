#ifndef AGENTPROJECT_SENSOR_H
#define AGENTPROJECT_SENSOR_H

#include "Map.h"
#include <vector>

class Sensor {
public:

	Sensor(Map*);
	~Sensor();

	bool isJewel();
	std::pair<int, int> locateAgent();
    std::vector<std::pair<int, int>> getDustCoords();
    void removeDust();
    int dustyCells();

private:
	Map* map;
	std::vector<std::pair<int, int>> dustCoords;

};

#endif //AGENTPROJECT_SENSOR_H
