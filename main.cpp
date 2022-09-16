#define LEARNING_RATE 4

#include <iostream>
#include <thread>

#include "Map.h"

using namespace std;

int main()
{
	srand(time(nullptr));

	Map *mp = new Map();

	cout << *mp << endl;

	return 0;
}

