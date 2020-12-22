#pragma once

#include <vector>
#include <algorithm>
#include <map>

#include "graph.h"
#include "edge.h"
#include "airport.h"
using namespace std;

typedef string Vertex;
class dijkstra
{
public:
    //graph creation
    dijkstra(Graph g, Vertex source);

    Graph g_;
    Vertex source_;
    int numofairport;
    map<Vertex, int> stops;
    map<Vertex, double> actualdistance;
    map<Vertex, double> distance;
    void printPaths() const;
    void printPath(Vertex dest);
    void printmin_and_max();
    Vertex getMax();
    Vertex getMin();

    map<Vertex, Vertex> path;
    string getpaths(Vertex source, Vertex dest);
};
