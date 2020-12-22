#include "dijkstra.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;
#define INF numeric_limits<double>::max()
typedef pair<double, Vertex> dis_node;

typedef string Vertex;

dijkstra::dijkstra(Graph g, Vertex source) : g_(true, true)
{
	g_ = g;
	source_ = source;

	// if the node doens't have any edge
	if (g_.adjacency_list[source].size() == 0)
	{
		for (auto &v : g_.getVertices())
		{

			distance[v] = 0;
		}
	}

	for (auto &v : g_.getVertices())
	{
		distance[v] = +INF;
	}

	distance[source] = 0;

	priority_queue<dis_node, vector<dis_node>, greater<dis_node>> Q; //min distance , defined by d[v]

	Q.push(make_pair(0, source));

	while (!Q.empty())
	{
		Vertex u = Q.top().second; // get minimum distance of vertex.
								   //remove this node from the priority queue.
		Q.pop();
		for (auto it = g_.adjacency_list[u].begin(); it != g_.adjacency_list[u].end(); it++)
		{
			Vertex v = (*it).first;
			int weight = g_.getEdgeWeight(u, v);
			if (distance[v] > distance[u] + weight)
			{
				distance[v] = distance[u] + weight;
				Q.push(make_pair(distance[v], v));
				path[v] = u;
			}
		}
	}

	for (auto it = distance.begin(); it != distance.end(); it++)
	{
		if ((*it).second != +INF)
		{
			actualdistance[(*it).first] = (*it).second;
		}
	}

	numofairport = actualdistance.size();
}

// Find the shortest paths.

void dijkstra::printPaths() const
{

	cout << "Printing all path tree from the source node"
		 << ".|n";

	if (g_.adjacency_list[source_].size() == 0)
	{
		cout << "this node doesn't have any edge to other nodes" << endl;
		return;
	}

	for (auto it = actualdistance.begin(); it != actualdistance.end(); it++)
	{

		cout << "Distance to the node   " << (*it).first << "  from node  " << source_ << "  is " << (*it).second << endl;
	}

	cout << "the number of connected airport is " << numofairport << endl;
}

void dijkstra::printPath(Vertex dest)
{
	cout << "Distance from the node  " << source_ << " to " << dest << " is " << distance[dest] << endl;
}

void dijkstra::printmin_and_max()
{

	//pair<Vertex, double> minimum = *min_element(mymap.begin(), mymap.end(),

	map<Vertex, double> actualdistance2 = actualdistance;
	actualdistance2.erase(source_);

	//pair<Vertex, double> maximum = *max_element(mymap.begin(), mymap.end(),

	map<Vertex, double>::iterator max = max_element(actualdistance.begin(), actualdistance.end(), [](const pair<Vertex, double> &a, const pair<Vertex, double> &b) -> bool { return a.second < b.second; });
	map<Vertex, double>::iterator minimum = min_element(actualdistance2.begin(), actualdistance2.end(), [](const pair<Vertex, double> &a, const pair<Vertex, double> &b) -> bool { return a.second < b.second; });

	cout << "Nearest airport from " << source_ << " is " << minimum->first << " distance: " << minimum->second << endl;

	cout << "Farthest airport from " << source_ << " is " << max->first << " distance: " << max->second << endl;
}

Vertex dijkstra::getMax()
{
	map<Vertex, double>::iterator max = max_element(actualdistance.begin(), actualdistance.end(), [](const pair<Vertex, double> &a, const pair<Vertex, double> &b) -> bool { return a.second < b.second; });
	Vertex aa = max->first;
	return aa;
}

Vertex dijkstra::getMin()
{

	map<Vertex, double> actualdistance2 = actualdistance;
	actualdistance2.erase(source_);
	map<Vertex, double>::iterator minimum = min_element(actualdistance2.begin(), actualdistance2.end(), [](const pair<Vertex, double> &a, const pair<Vertex, double> &b) -> bool { return a.second < b.second; });

	Vertex aa = minimum->first;
	return aa;
}

string dijkstra::getpaths(Vertex source, Vertex dest)
{
	string ret = dest;

	if (path[dest] == source)
	{
		return ret + " " + source;
	}

	return ret + " " + getpaths(source, path[dest]);
}
