#ifndef AGENTPROJECT_SENSOR_H
#define AGENTPROJECT_SENSOR_H

#include "Agent.h"
#include <vector>

class Sensor : public Agent {
public:
	void getDirtCoords();
	bool isJewelInDirt();
private:
	std::vector<std::pair<int, int>> dirtCoords;
};

#endif //AGENTPROJECT_SENSOR_H
