#ifndef AGENTPROJECT_EFFECTOR_H
#define AGENTPROJECT_EFFECTOR_H
#include "Agent.h"

class Effector : public Agent {
public:
	void cleanCell();
	void pickupCell();
	int travelCost(int, int);
private:
};


#endif //AGENTPROJECT_EFFECTOR_H
