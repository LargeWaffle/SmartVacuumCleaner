vector<vector<int> > graph;

// map to store cost of edges
map<pair<int, int>, int> cost;

vector<int> uniform_cost_search(vector<int> goal, int start)
{
    // minimum cost upto
    // goal state from starting
    // state
    vector<int> answer;

    // create a priority queue
    priority_queue<pair<int, int> > queue;

    // set the answer vector to max value
    for (int i = 0; i < goal.size(); i++)
        answer.push_back(INT_MAX);

    // insert the starting index
    queue.push(make_pair(0, start));

    // map to store visited node
    map<int, int> visited;

    // count
    int count = 0;

    // while the queue is not empty
    while (queue.size() > 0) {

        // get the top element of the priority queue
        pair<int, int> p = queue.top();

        // pop the element
        queue.pop();

        // get the original value
        p.first *= -1;

        // check if the element is part of the goal list
        if (find(goal.begin(), goal.end(), p.second) != goal.end()) {

            // get the position
            int index = find(goal.begin(), goal.end(), p.second) - goal.begin();

            // if a new goal is reached
            if (answer[index] == INT_MAX)
                count++;

            // if the cost is less
            if (answer[index] > p.first)
                answer[index] = p.first;

            // pop the element
            queue.pop();

            // if all goals are reached
            if (count == goal.size())
                return answer;
        }

        // check for the non visited nodes
        // which are adjacent to present node
        if (visited[p.second] == 0)
            for (int i = 0; i < graph[p.second].size(); i++) {

                // value is multiplied by -1 so that
                // least priority is at the top
                queue.push(make_pair((p.first +
                                      cost[make_pair(p.second, graph[p.second][i])]) * -1,
                                     graph[p.second][i]));
            }

        // mark as visited
        visited[p.second] = 1;
    }

    return answer;
}