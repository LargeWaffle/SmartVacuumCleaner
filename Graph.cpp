#include "Graph.h"

using namespace std;

Graph::Graph(int LR)
{
    learning_rate = LR;

}

void Graph::buildGraph(std::vector< std::pair<int, int> > targets) {

}

bool Graph::DLS(int src, int target, int limit)
{
	if (src == target)
		return true;

	// If reached the maximum depth, stop recursing.
	if (limit <= 0)
		return false;

	// Recur for all the vertices adjacent to source vertex
	for (auto i = adj[src].begin(); i != adj[src].end(); ++i)
		if (DLS(*i, target, limit-1) == true)
			return true;

	return false;
}

// IDDFS to search if target is reachable from v.
// It uses recursive DFSUtil().
bool Graph::IDDFS(int src, int target, int max_depth)
{
	// Repeatedly depth-limit search till the
	// maximum depth.
	for (int i = 0; i <= max_depth; i++)
		if (DLS(src, target, i) == true)
			return true;

	return false;
}