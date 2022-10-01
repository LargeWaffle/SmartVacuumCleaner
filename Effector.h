#ifndef AGENTPROJECT_EFFECTOR_H
#define AGENTPROJECT_EFFECTOR_H

#include "Map.h"

class Effector {
public:

    Effector(Map*);
    ~Effector();

    void travel(int, int);
    int actOnCell(int, int);
private:
    Map * map;
};


#endif //AGENTPROJECT_EFFECTOR_H