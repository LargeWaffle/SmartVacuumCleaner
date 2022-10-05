#include "Agent.h"

#include <random>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

Agent::Agent(Map *mp, bool smart) {

	map = mp;
	problem = nullptr;
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

		for (int learning_rate = 1; learning_rate < MAX_LEARNING_RATE + 1; learning_rate++) { // first big boucle
			for (int iter_count = 1; iter_count < TEST_NUMBER + 1; iter_count++) { // second big boucle

				problem = new Graph(map);   // Beliefs

				auto start = high_resolution_clock::now();
				auto iter_timer = high_resolution_clock::now();

				vector<float> perf_per_iter;

				auto elapsed_time = false;

				while (!elapsed_time) { // third big boucle - representing one test

					perform(stepNumber, learning_rate);
					// cout << *map << endl;

					auto current_time = high_resolution_clock::now();
					auto iteration_time = duration_cast<seconds>(current_time - iter_timer) >= 1s;

					if (iteration_time) {
						perf_per_iter.push_back(perfEval());
						batteryUsed = 0;
						jewelCleaned = 0;
						iter_timer = high_resolution_clock::now();
					}

					elapsed_time = duration_cast<seconds>(current_time - start) >= TEST_DURATION;
				}

				perf_tab[learning_rate - 1][iter_count - 1] = evaluatePerf(perf_per_iter);
				cout << perf_tab[learning_rate - 1][iter_count - 1] << " ";

			}
			cout << endl;

		}

		for (int i = 0; i < MAX_LEARNING_RATE; i++) {
			cout << "Learning rate " << i + 1 << " : " << evaluatePerf(perf_tab[i]) << endl;
		}

		float curBest = 1000.0;
		int best_learning_rate = 0;

		for (int i = 0; i < MAX_LEARNING_RATE; i++) {
			if (evaluatePerf(perf_tab[i]) < curBest) {
				curBest = evaluatePerf(perf_tab[i]);
				best_learning_rate = i;
			}
		}

		cout << "best learning rate : " << best_learning_rate + 1 << endl;

		delete problem;
		problem = new Graph(map);

		perform(stepNumber, best_learning_rate);
	}

}

vector<Graph::node> Agent::getActions() {

	if (smartAgent)
		return problem->Astar(sens->locateAgent());
		// pour la seconde version du a*, remplacer la ligne du dessus par
		// return problem->AstarTwo(sens->locateAgent(), sens->getDustCoords());
	else
		return problem->BFS(sens->locateAgent());
}

float Agent::perfEval() const {

	float dustAmount = sens->getDustCoords().size();
	auto perfScore = (float) (((dustAmount / (MAP_SIZE * MAP_SIZE)) * batteryUsed) + JEWEL_PENALTY * jewelCleaned);

	return perfScore;
}

float Agent::evaluatePerf(vector<float> perfs) {

	float avg = 0.0;

	if (!perfs.empty())
		avg = accumulate(perfs.begin(), perfs.end(), 0.0) / perfs.size();

	return avg;
}

void Agent::perform(int &stepNumber, const int &lr) {

	if (actionList.empty() || stepNumber >= lr) {
		if (stepNumber >= lr)
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

	stepNumber += eff->actOnCell(targetAction, lr - stepNumber);
	batteryUsed += stepNumber;

	actionList.pop_back();
}