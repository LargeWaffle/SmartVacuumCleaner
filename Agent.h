#ifndef AGENTPROJECT_AGENT_H
#define AGENTPROJECT_AGENT_H

#include <queue>
#include "Map.h"
#include "Effector.h"
#include "Sensor.h"
#include "Graph.h"

#define MAX_LEARNING_RATE 6
#define TEST_DURATION 60s
#define TEST_NUMBER 10
#define JEWEL_PENALTY 1

class Agent {

public:
	explicit Agent(Map *mp, bool smart = false);
	~Agent();

	void agentWork();
    std::vector<Graph::node> getActions();

	Sensor * sens;
	Effector * eff;

	bool smartAgent;
	std::vector<Graph::node> actionList;    // Intentions

	int jewelCleaned = 0;
	int batteryUsed = 0;

	float perfEval() const;
	float evaluatePerf(std::vector<float>);
	void perform(int&, const int&);

private:

	Map * map;
    Graph * problem;
};


#endif //AGENTPROJECT_AGENT_H
