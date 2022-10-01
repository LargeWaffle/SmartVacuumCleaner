#include "Agent.h"

#include <random>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
	vector<vector<float>> perf_tab(MAX_LEARNING_RATE, vector<float>(MAX_LEARNING_RATE));


	while (true) {

		for (int start_learning_rate = 1; start_learning_rate < MAX_LEARNING_RATE; start_learning_rate++) { // first big boucle
			for (int iter_count = 1; iter_count < 6; iter_count++) { // second big boucle

				problem = new Graph(MAX_LEARNING_RATE, sens->locateAgent(), map);

				auto start = high_resolution_clock::now();
				auto iter_timer = high_resolution_clock::now();

				vector<float> perf_per_iter(10, 0); // put 60 HERE

				auto elapsed_time = false;

				while (!elapsed_time)  { // third big boucle - representing one test
					if (actionList.empty() || stepNumber >= start_learning_rate) {
						if (stepNumber >= start_learning_rate)
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

					stepNumber += eff->actOnCell(targetAction, start_learning_rate - stepNumber);
					batteryUsed += stepNumber;

					if (targetAction == 2 && map->getCell(targetLocation.first, targetLocation.second)->hasJewel())
						jewelCleaned += 1;

					actionList.pop_back();

					auto current_time = high_resolution_clock::now();
					auto iteration_time = duration_cast<seconds>(current_time - iter_timer) >= 1s;

					if (iteration_time) {
						perf_per_iter.push_back(perfEval());
						batteryUsed = 0;
						jewelCleaned = 0;
						iter_timer = high_resolution_clock::now();
					}

					elapsed_time = duration_cast<seconds>(current_time - start) >= 10s; // put 60 HERE
				}

				perf_tab[start_learning_rate-1][iter_count-1] = evaluatePerf(perf_per_iter);
				//cout << stepNumber << endl;
				//cout << *map << endl;
				cout << perf_tab[start_learning_rate-1][iter_count-1] << " ";

			}
			cout << endl;

		}
	}

}

vector<Graph::node> Agent::getActions() {

	if (smartAgent)
		return problem->Astar(sens->locateAgent());
	else
		return problem->BFS(sens->locateAgent());
}

float Agent::perfEval(){

	float perfScore = (float)(sens->getDustCoords().size()/MAP_SIZE*MAP_SIZE) * batteryUsed + jewelCleaned;

	return perfScore;
}

float Agent::evaluatePerf(vector<float> perfs){

	float avg = 0.0;

	if (!perfs.empty())
		avg = accumulate(perfs.begin(), perfs.end(), 0.0) / perfs.size();

	return avg;
}
