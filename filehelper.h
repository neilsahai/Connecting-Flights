#pragma once

#include "filehelper.h"
#include "airport.h"
#include "dijkstra.h"
#include "landmark.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

//given address of airport file, read into airport structure
//return map of airport id to airport
map<string, airport> make_airports(string file_name);

//given routes file, read into dictionary
//return map of source to vec of all destinations
map<string, vector<string>> make_routes(string file_name);

//given map of airport id to airport structure and map of airport id to destination airport IDs
//return a weighted, directed graph of all airports and their connecting routes
Graph make_graph(map<string, airport> airports, map<string, vector<string>> routes);

//given airports, dijkstra of airport, landmark, and list of destinations and landmarks
//build interesting statistics file to file name
void make_statistics_file(dijkstra d, landmark l, map<string, airport> airports, string source, string file_name, vector<string> landmarks, vector<string> destinations);