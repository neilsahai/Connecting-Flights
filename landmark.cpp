#include <vector>
#include <algorithm>
#include <map>

#include "landmark.h"

using namespace std;

//constructor for nonpre-calculated landmark
landmark::landmark(Graph g, Vertex source) : g_(true, true), d_(g_, source)
{
	g_ = g;
	source_ = source;
	d_ = dijkstra(g, source);
}

//find shortest route from a to b through c
int landmark::find_distance(Vertex dest, Vertex landmark)
{
	map<Vertex, double> landmark_dijkstra = dijkstra(g_, landmark).distance;

	//graph is not directed so we must do 2 dijkstra instead of 1

	if (d_.distance.find(landmark) == d_.distance.end())
	{
		cout << source_ << " is not connected to " << landmark << endl;
		return -1;
	}

	if (landmark_dijkstra.find(dest) == landmark_dijkstra.end())
	{
		cout << landmark << " is not connected to " << dest << endl;
		return -1;
	}

	return d_.distance[landmark] + landmark_dijkstra[dest];
}