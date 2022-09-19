#ifndef AGENTPROJECT_MAP_H
#define AGENTPROJECT_MAP_H

#define DIRT_SPAWN_RATE 5
#define JEWEL_SPAWN_RATE 2

#define INITIAL_DIRT_SPAWN_RATE 20
#define INITIAL_JEWEL_SPAWN_RATE 5

#define MAP_SIZE 5

#include <iostream>
#include <vector>
#include <utility>
#include <mutex>

class Cell {
	friend class Map;
private:
	bool m_vacuum = false;
	bool m_dirt = false;
	bool m_jewel = false;

public:
	Cell(double dirtRate = 0.0, double jewelRate = 0.0); // constructor
	~Cell();
	bool hasDirt() const;
	bool hasJewel() const;
	bool hasVacuum() const;

	void setDirt(bool);
	void setJewel(bool);
	void setVacuum(bool);

	friend std::ostream& operator<<(std::ostream&, const Cell& );

	void spawnUpdate();
};

class Map {
public:
	Map();
	~Map();

	int getMapSize();
	Cell* getCell(int, int);

	void mapUpdator();
	void objSpawn();    // thread func

	void clean();
	void pickup();

	std::pair<int, int> getVacuum();
	bool go;

	friend std::ostream& operator<<(std::ostream&, const Map& );

private:
	std::vector< std::vector<Cell*> > map;
};

#endif //AGENTPROJECT_MAP_H
