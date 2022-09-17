#define LEARNING_RATE 4

#include <iostream>
#include <thread>

#include "Map.h"

using namespace std;

int main()
{
	srand(time(nullptr));

	Map *mp = new Map();

	thread env(&Map::objSpawn, mp);
	env.join();

	// thread agent(); ou just le main en fait

	return 0;
}

