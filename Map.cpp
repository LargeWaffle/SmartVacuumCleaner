#include "Map.h"

#include <thread>
#include <chrono>
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
        this_thread::sleep_for(chrono::seconds(1));
	    mapUpdator();
		// cout << *this << endl;
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

	setVacuum(false);

	int dustProb = rand() % 100 + 1;
	int jewelProb = rand() % 100 + 1;

	if (dustProb < dustSpawnRate)
		setDust(true);

	if (jewelProb < jewelSpawnRate)
		setJewel(true);
}

Cell::~Cell() {

}

void Cell::spawnUpdate() {

	int dustProb = rand() % 100 + 1; // FIX IS HERE
	int jewelProb = rand() % 100 + 1; // FIX IS HERE

	if (dustProb < DUST_SPAWN_RATE)
		setDust(true);

	if (jewelProb < JEWEL_SPAWN_RATE)
		setJewel(true);
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

	string res;

	if (c.hasDust())
		res.append("D");

	if (c.hasVacuum())
		res.append("V");

	if (c.hasJewel())
		res.append("J");

	if (c.hasDust() && c.hasJewel() && c.hasVacuum())
		res = "A";

	if (res.empty())
		res = ".";

	res.append(" ");

	output << res;

	return output;
}
