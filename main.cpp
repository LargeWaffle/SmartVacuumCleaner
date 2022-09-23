#include <iostream>
#include <thread>

#include "Map.h"
#include "Agent.h"

using namespace std;

int main()
{
	srand(time(nullptr));

	Map *mp = new Map();
	Agent *vacuum = new Agent(mp);

	thread env(&Map::objSpawn, mp);
	// thread roomba(&Agent::agentWork, vacuum);

	env.join();

	// roomba.join();

	return 0;
}
