#include "Agent.h"

#include <random>
#include <thread>

using namespace std;

Agent::Agent(Map *mp, bool smart) {

    map = mp;
    smartAgent = smart;

    int coordX = rand() % mp->getMapSize();
    int coordY = rand() % mp->getMapSize();

    map->getCell(coordX, coordY)->setVacuum(true);

    eff = new Effector(mp);
    sens = new Sensor(mp);

    actionList = {};
}

Agent::~Agent() {

    delete eff;
    delete sens;

}

void Agent::agentWork() {

    int stepNumber = 0;
    problem = new Graph(LEARNING_RATE, sens->locateAgent(), map);

    while (true) {

        cout << stepNumber << endl;
        cout << *map << endl;

        if (actionList.empty() || stepNumber >= LEARNING_RATE) {
            if (stepNumber >= LEARNING_RATE)
                stepNumber = 0;
            actionList = getActions();
            this_thread::sleep_for(chrono::milliseconds(1));
        }

        int targetAction = actionList.back()->actionData;
        pair<int, int> targetLocation = actionList.back()->location;

        if (sens->locateAgent() != targetLocation) {
            eff->travel(targetLocation.first, targetLocation.second);
            stepNumber++;
        }

        stepNumber += eff->actOnCell(targetAction, LEARNING_RATE - stepNumber);

        actionList.pop_back();

    }

}

vector<Graph::node> Agent::getActions() {

    vector<pair<int, int>> targets = sens->getDustCoords();  // Desires ? Function returns number of steps to take

    if (smartAgent)
        return problem->Astar(sens->locateAgent(), targets);
    else
        return problem->BFS(sens->locateAgent());
}
