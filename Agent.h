#ifndef AGENTPROJECT_AGENT_H
#define AGENTPROJECT_AGENT_H

#include "Map.h"
#include "Effector.h"
#include "Sensor.h"
#include "Graph.h"

#define LEARNING_RATE 4

class Agent {

public:
	Agent(Map *mp);
	~Agent();

	void agentWork();
	//std::vector< std::pair<int, int> > getActions(Graph, int);

	Sensor * sens;
	Effector * eff;

	int nbTargets;  // Desires
	std::vector< std::pair<int, int> > actionList;    // Intentions

private:

	float score = 0.0;

	// serie d'etat/etat a atteindre
	Map * map;
};


#endif //AGENTPROJECT_AGENT_H
