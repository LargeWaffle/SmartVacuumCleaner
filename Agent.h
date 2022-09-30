#ifndef AGENTPROJECT_AGENT_H
#define AGENTPROJECT_AGENT_H

#include <queue>
#include "Map.h"
#include "Effector.h"
#include "Sensor.h"
#include "Graph.h"

#define LEARNING_RATE 16

class Agent {

public:
	Agent(Map *mp, bool smart = false);
	~Agent();

	void agentWork();
    std::vector<Graph::node> getActions();

	Sensor * sens;
	Effector * eff;

	bool smartAgent;
	std::vector<Graph::node> actionList;    // Intentions

private:

	float score = 0.0;

	Map * map;
    Graph * problem;
};


#endif //AGENTPROJECT_AGENT_H
