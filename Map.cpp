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
			v.push_back(new Cell(INITIAL_DUST_SPAWN_RATE, INITIAL_JEWEL_SPAWN_RATE));
		map.push_back(v);
	}
}

// Destructor
Map::~Map() {

	for (auto & i : map)
		for (auto & j : i)
			delete j;
}

int Map::getMapSize() {
	return MAP_SIZE;
}

Cell* Map::getCell(int x, int y) {
	return map[x][y];
}

// Updator
void Map::mapUpdator(){

	for (auto & i : map)
		for (auto & j : i)
			j->spawnUpdate();
}

void Map::objSpawn(){
	while(true) {
        if (go)
		    mapUpdator();
        go = false;
	}
}

void Map::clean() {
	getCell(getVacuum().first, getVacuum().second)->m_dust = false;
}

void Map::pickup() {
	getCell(getVacuum().first, getVacuum().second)->m_jewel = false;
}

pair<int, int> Map::getVacuum() {

	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
			if(map[i][j]->hasVacuum())
				return make_pair(i,j);
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
Cell::Cell(double dustSpawnRate, double jewelSpawnRate) {

	m_vacuum = false;

	int dustProb = rand() % 100 + 1;
	int jewelProb = rand() % 100 + 1;

	if (dustProb < dustSpawnRate)
		m_dust = true;

	if (jewelProb < jewelSpawnRate)
		m_jewel = true;
}

Cell::~Cell() {

}

void Cell::spawnUpdate() {

	int dustProb = rand() % 100 + 1; // FIX IS HERE
	int jewelProb = rand() % 100 + 1; // FIX IS HERE

	if (dustProb < DUST_SPAWN_RATE)
		m_dust = true;

	if (jewelProb < JEWEL_SPAWN_RATE)
		m_jewel = true;
}

bool Cell::hasDust() const {
	return m_dust;
}

bool Cell::hasJewel() const {
	return m_jewel;
}

bool Cell::hasVacuum() const {
	return m_vacuum;
}

void Cell::setDust(bool arg) {
	m_dust = arg;
}

void Cell::setJewel(bool arg) {
	m_jewel = arg;
}

void Cell::setVacuum(bool arg) {
	m_vacuum = arg;
}

ostream& operator<<(ostream& output, const Cell& c) {
	if (c.m_dust && c.m_jewel && c.m_vacuum)
		output << "A ";
	else if (c.m_dust && c.m_jewel)
		output << "B ";
	else if (c.m_dust && c.m_vacuum)
		output << "DV";
	else if (c.m_jewel && c.m_vacuum)
		output << "JV";
	else if (c.m_dust)
		output << "D ";
	else if (c.m_vacuum)
		output << "V ";
	else if (c.m_jewel)
		output << "J ";
	else
		output << ". ";

	return output;
}
