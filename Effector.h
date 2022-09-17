#ifndef AGENTPROJECT_EFFECTOR_H
#define AGENTPROJECT_EFFECTOR_H

#include "Map.h"

class Effector {
public:

	Effector(Map*);
	~Effector();

	void cleanCell();
	void pickupCell();
	int travelCost(int, int);
	void travel(int, int);
private:
	Map * map;
};


#endif //AGENTPROJECT_EFFECTOR_H
