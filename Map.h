#ifndef AGENTPROJECT_MAP_H
#define AGENTPROJECT_MAP_H

#define DUST_SPAWN_RATE 6
#define JEWEL_SPAWN_RATE 3

#define INITIAL_DUST_SPAWN_RATE 20
#define INITIAL_JEWEL_SPAWN_RATE 5

#define MAP_SIZE 5

#include <iostream>
#include <vector>

#include <mutex>

class Cell {
	friend class Map;
private:
	bool m_vacuum = false;
	bool m_dust = false;
	bool m_jewel = false;

public:
	Cell(double dustRate = 0.0, double jewelRate = 0.0); // constructor
	~Cell();
	bool hasDust() const;
	bool hasJewel() const;
	bool hasVacuum() const;

	void setDust(bool);
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

	friend std::ostream& operator<<(std::ostream&, const Map& );

private:
	std::vector< std::vector<Cell*> > map;
};

#endif //AGENTPROJECT_MAP_H
