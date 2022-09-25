#ifndef AGENTPROJECT_GRAPH_H
#define AGENTPROJECT_GRAPH_H

#include <vector>

class Graph {

public:

    Graph(int, std::pair<int, int>); // Constructor
    ~Graph();

    void buildGraph(std::vector< std::pair<int, int> >);
    void generateChildren(std::vector< std::pair<int, int> >, node);
    int getDistance(std::pair<int, int>, std::pair<int, int>);

    //std::vector<std::pair<int, int>> UCS();

};


#endif //AGENTPROJECT_GRAPH_H
