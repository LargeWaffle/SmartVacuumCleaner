#ifndef AGENTPROJECT_MAP_H
#define AGENTPROJECT_MAP_H

#define DIRT_SPAWN_RATE 0.5
#define JEWEL_SPAWN_RATE 0.1

#define INITIAL_DIRT_SPAWN_RATE 0.2
#define INITIAL_JEWEL_SPAWN_RATE 0.05

#define MAP_SIZE 5

#include <iostream>
#include <vector>

class Cell {
	friend class Map;
private:
	bool m_vacuum; // à examiner
	bool m_dirt = false;
	bool m_jewel = false;
public:
	Cell(double x = 0.0, double y = 0.0); // constructor
	~Cell();
	bool hasDirt() const;
	bool hasJewel() const;

	friend std::ostream& operator<<(std::ostream&, const Cell& );

	void spawnUpdate();
};

class Map {
public:
	Map();
	~Map();

	int getMapSize();

	void mapUpdator();

	friend std::ostream& operator<<(std::ostream&, const Map& );
private:
	std::vector< std::vector<Cell*> > map;
};

#endif //AGENTPROJECT_MAP_H
