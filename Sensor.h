#ifndef AGENTPROJECT_SENSOR_H
#define AGENTPROJECT_SENSOR_H

#include "Map.h"
#include <vector>

class Sensor {
public:

	Sensor(Map*);
	~Sensor();

	void retrieveDustCoords();
	bool isJewel();
	std::pair<int, int> locate();
    std::vector<std::pair<int, int>> getDustCoords();
    void removedDust();
    int dustyCells();

private:
	Map* map;
	std::vector<std::pair<int, int>> dustCoords;

};

#endif //AGENTPROJECT_SENSOR_H
