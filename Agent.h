#ifndef AGENTPROJECT_AGENT_H
#define AGENTPROJECT_AGENT_H

#include <queue>
#include "Map.h"
#include "Effector.h"
#include "Sensor.h"
#include "Graph.h"

#define LEARNING_RATE 4

class Agent {

public:
	Agent(Map *mp, bool smart = false);
	~Agent();

	void agentWork();
	std::pair<bool, std::pair<int, int>> BFS ();
	void expandNode(std::pair<int, int> pos, std::queue< std::pair<int, int>>&, std::vector< std::pair<int, int>>&);
	bool isNodeUnvisited(std::pair<int, int> , std::vector< std::pair<int, int>>&);
	void getActions(Graph, std::vector<std::pair<int, int> > );

	Sensor * sens;
	Effector * eff;

	int nbTargets;  // Desires
	std::vector< std::pair<bool, std::pair<int, int>> > actionList;    // Intentions

private:

	float score = 0.0;

	// serie d'etat/etat a atteindre
	Map * map;
	bool smartAgent;
};


#endif //AGENTPROJECT_AGENT_H
