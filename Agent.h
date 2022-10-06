#ifndef AGENTPROJECT_AGENT_H
#define AGENTPROJECT_AGENT_H

#include <queue>
#include "Map.h"
#include "Effector.h"
#include "Sensor.h"
#include "Graph.h"

// Variable définissant le w de la pénalité pour un bijou aspiré
#define JEWEL_PENALTY 1

// Variables pour les tests
#define MAX_LEARNING_RATE 6
#define TEST_DURATION 10s
#define TEST_NUMBER 5


class Agent {

public:
	explicit Agent(Map *mp, bool smart = false);
	~Agent();

	void agentWork(int, int);
    std::vector<Graph::node> getActions(int);

	Sensor * sens;
	Effector * eff;

	bool smartAgent;
	std::vector<Graph::node> actionList;    // Intentions

	int jewelCleaned = 0;
	int batteryUsed = 0;

	float perfEval() const;
	float evaluatePerf(std::vector<float>);
	void perform(int, const int, int);
    int runTest();

private:

	Map * map;
    Graph * problem;
};


#endif //AGENTPROJECT_AGENT_H
