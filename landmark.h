#pragma once

#include <vector>
#include <algorithm>
#include <map>

#include "graph.h"
#include "edge.h"
#include "airport.h"
#include "dijkstra.h"

using namespace std;

typedef string Vertex;

class landmark
{
public:
    //constructor for landmark
    landmark(Graph g, Vertex source);

    //landmark method
    int find_distance(Vertex dest, Vertex landmark);

private:
    Graph g_;
    dijkstra d_;
    Vertex source_;
};