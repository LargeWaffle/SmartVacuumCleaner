#define LEARNING_RATE 4

#include <iostream>
#include <thread>

#include "Map.h"
#include "Agent.h"

using namespace std;

int main()
{
	srand(time(nullptr));

	Map *mp = new Map();

	Agent * vacuum = new Agent(mp);

	int newCoordX = mp->getVacuum().first, newCoordY = mp->getVacuum().second;

	while (true) {

		if(newCoordX == mp->getVacuum().first && newCoordY == mp->getVacuum().second)
		{
			newCoordX = rand() % mp->getMapSize();
			newCoordY = rand() % mp->getMapSize();
			cout << "new coord is " << newCoordX << "," << newCoordY << endl;
		}
		else
		{
			vacuum->eff->travel(newCoordX, newCoordY);
		}

		cout << "IN MAIN : " << endl << *mp << endl;
	}
	//thread env(&Map::objSpawn, mp);
	//env.join();

	// thread agent(); ou just le main en fait

	return 0;
}
