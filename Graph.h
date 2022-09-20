//
// Created by marti on 20/09/2022.
//

#ifndef AGENTPROJECT_GRAPH_H
#define AGENTPROJECT_GRAPH_H

#include <vector>
#include <utility>

class Graph {

public:

    Graph(int); // Constructor
    void buildGraph();



private:
    class Node{
        public:

            Node(std::pair<int, int> dust_data, std::vector<Node*> child_list = {})
            : location(dust_data){};
        private:
            float score = 0.0;
            std::pair<int, int> location;
            std::vector<Node*> children;
    };
    typedef Node * node;

    node root;
    int learning_rate;

};


#endif //AGENTPROJECT_GRAPH_H
