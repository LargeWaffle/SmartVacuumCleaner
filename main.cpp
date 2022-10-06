#include <iostream>
#include <thread>

#include "Map.h"
#include "Agent.h"

using namespace std;

int main()
{
    int userChoice = 0;
    int s = MAX_LEARNING_RATE*TEST_NUMBER*stoi(to_string(chrono::duration_cast<chrono::seconds>(TEST_DURATION).count()).substr(0, to_string(chrono::duration_cast<chrono::seconds>(TEST_DURATION).count()).find('s')))/60;
    while (userChoice != 1 && userChoice != 2 && userChoice != 3 && userChoice != 4) {
        cout << "Welcome to the Roomboss experience ! We have different modes available :\n"
                "1 - Run Roomboss with a BFS algorithm, paired with Roomboss's best learning rate.\n"
                "2 - Run Roomboss with a A* algorithm, paired with Roomboss's best learning rate.\n"
                "3 - Run Roomboss with our second A* algorithm (read report page 21 before)\n"
                "4 - Make Roomboss run a " << s << "min test to estimate the best learning rate for him. "
                "(read report page 11 before)\n"
                "\tHe will then start running with a A* algorithm and this best learning rate.\n\n"
                "In all choices, when the map prints, each cell of the map is represented by a . : \n"
                "- the cell where Roomboss is located is represented by V, \n"
                "- cells containing jewels or dust are represented by J or D respectively, \n"
                "- cells containing two elements are represented by their two letters,\n"
                "- and cells containing all three elements are represented by an A." << endl;
        cin >> userChoice;
    }

    srand(time(nullptr));
    Agent *vacuum;
    Map *mp = new Map();
    if (userChoice == 1)
        vacuum = new Agent(mp, false);
    else
        vacuum = new Agent(mp, true);

    thread env(&Map::objSpawn, mp);
    thread roomba(&Agent::agentWork, vacuum, userChoice);

    env.join();
    roomba.join();

	return 0;
}
