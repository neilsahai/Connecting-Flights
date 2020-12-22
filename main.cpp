#include "filehelper.h"
#include "airport.h"
#include "graph.h"
#include "BFS.h"
#include "dijkstra.h"
#include "landmark.h"

#include <vector>
#include <map>
#include <iostream>

#define airports_file "data/airports.dat"
#define routes_file "data/routes.dat"
#define BFS_output "output/bfs.txt"
#define statistics_output "output/statistics.txt"
#define ex_airport "3830"

using namespace std;

int main()
{
	//Read through airports file
	cout << "Reading " << airports_file << endl;
	map<string, airport> airports = make_airports(airports_file);

	//Read through routes file
	cout << "Reading " << routes_file << endl;
	map<string, vector<string>> routes = make_routes(routes_file);

	//Create weighted graph from our data
	cout << "Creating graph" << endl;
	Graph graph = make_graph(airports, routes);
	cout << "Graph is done." << endl;

	//Performs the process of printing the vertices in BFS order
	BFS bfs;
	Vertex source = "1";
	bfs.print(source, graph, BFS_output);
	cout << "Traversed graph in BFS order. Output file written to " << BFS_output << endl;

	//Perform sample dijkstra's algorithm using O'Hare airport
	cout << "Computing sample Dijkstra's algorithm for airport: " << airports[ex_airport].name_ << endl;
	dijkstra shortest_graph = dijkstra(graph, ex_airport);
	cout << "Completed Dijkstra's algorithm." << endl;
	//shortest_graph.getpaths(shortest_graph.source_, shortest_graph.getMax());

	//Create landmark object with O'Hare airport
	landmark land = landmark(graph, ex_airport);

	//selected airports to populate statistics file
	vector<string> landmarks{"18", "3484", "3577", "3697", "1824"};
	vector<string> destinations{"507", "2279", "3364", "813", "2560"};

	//Create interesting statistics file utilizing dijkstra and landmark
	make_statistics_file(shortest_graph, land, airports, ex_airport, statistics_output, landmarks, destinations);
	cout << "Statistics file for airport: " << airports[ex_airport].name_ << " written to " << statistics_output << endl;

	return 0;
}
