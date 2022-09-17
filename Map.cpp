#include "Map.h"

#include <random>

using namespace std;

// Constructor
Map::Map()
{
	for (int i = 0; i < MAP_SIZE; i++)
	{
		vector<Cell*> v;
		for (int j = 0; j < MAP_SIZE; j++)
			v.push_back(new Cell(INITIAL_DIRT_SPAWN_RATE, INITIAL_JEWEL_SPAWN_RATE));
		map.push_back(v);
	}
}

// Destructor
Map::~Map() {

	for (auto & i : map)
		for (auto & j : i)
			delete j;
}

// Updator
void Map::mapUpdator(){

	for (auto & i : map)
		for (auto & j : i)
			j->spawnUpdate();

}

void Map::objSpawn(){

	while(true){
		mapUpdator();
		// cout << *this << endl;
	}
}

int Map::getMapSize() {
	return MAP_SIZE;
}

ostream &operator<<(ostream & output, const Map& mp) {

	for (auto & i : mp.map)
	{
		for (auto & j : i)
			output <<*j << " ";
		output << endl;
	}
	return output;
}

// Constructor
Cell::Cell(double dirtSpawnRate, double jewelSpawnRate) {

	m_vacuum = false;

	int dirtProb = rand() % 100 + 1;
	int jewelProb = rand() % 100 + 1;

	if (dirtProb < INITIAL_DIRT_SPAWN_RATE)
		m_dirt = true;

	if (jewelProb < INITIAL_JEWEL_SPAWN_RATE)
		m_jewel = true;
}

Cell::~Cell() {

}

void Cell::spawnUpdate() {

	int dirtProb = rand() % 100 + 1;
	int jewelProb = rand() % 100 + 1;

	if (dirtProb < DIRT_SPAWN_RATE)
		m_dirt = true;

	if (jewelProb < JEWEL_SPAWN_RATE)
		m_jewel = true;

}

bool Cell::hasDirt() const {
	return m_dirt;
}

bool Cell::hasJewel() const {
	return m_jewel;
}

ostream& operator<<(ostream& output, const Cell& c) {
	if (c.m_dirt && c.m_jewel)
		output << "B ";
	else if (c.m_dirt)
		output << "D ";
	else if (c.m_jewel)
		output << "J ";
	else
		output << ". ";

	return output;
}