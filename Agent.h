#ifndef AGENTPROJECT_AGENT_H
#define AGENTPROJECT_AGENT_H

#include "Map.h"
#include "Effector.h"
#include "Sensor.h"

#define LEARNING_RATE 4

class Agent {

public:
	Agent(Map *mp);
	~Agent();

	void agentWork();

	Sensor * sens;
	Effector * eff;
private:

	float score = 0.0;

	// serie d'etat/etat a atteindre
	Map * map;
	int destX, destY;
};


#endif //AGENTPROJECT_AGENT_H
