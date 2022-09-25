#ifndef AGENTPROJECT_EFFECTOR_H
#define AGENTPROJECT_EFFECTOR_H

#include "Map.h"

class Effector {
public:

	Effector(Map*);
	~Effector();

	int travelCost(int, int);
	void travel(int, int);
	void actOnCell(bool);
private:
	Map * map;
};


#endif //AGENTPROJECT_EFFECTOR_H
