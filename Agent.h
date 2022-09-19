#ifndef AGENTPROJECT_AGENT_H
#define AGENTPROJECT_AGENT_H

#include "Map.h"
#include "Effector.h"
#include "Sensor.h"

class Agent {

public:
	Agent(Map *mp);
	~Agent();

	int getX();
	int getY();

	void doOneMove();

	Sensor * sens;
	Effector * eff;
private:

	float score = 0.0;

	// serie d'etat/etat a atteindre
	Map * map;
	int destX, destY;
};


#endif //AGENTPROJECT_AGENT_H
