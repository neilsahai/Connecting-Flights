#include "../filehelper.h"
#include "../airport.h"
#include "../graph.h"
#include "../BFS.h"
#include "../dijkstra.h"
#include "../landmark.h"
#include "catch/catch.hpp"

#include <iostream>

#define BFS_output "output/bfs.txt"

//###################
//Airport Tests
//###################

TEST_CASE("airport constructor correctly constructs an airport")
{
    string id = "1";
    string name = "Goroka Airport";
    string latitude = "-6.081689834590001";
    string longitude = "145.391998291";
    airport airport = ::airport(id, name, latitude, longitude);

    REQUIRE(airport.ID_ == id);
    REQUIRE(airport.name_ == name);
    REQUIRE(airport.latitude_ == latitude);
    REQUIRE(airport.longitude_ == longitude);
    cout << "Finished test airport constructor." << endl;
}

TEST_CASE("get_distance correctly gets the distance between two airports")
{
    //Mixed Latitude Longitudes
    airport airport1 = airport("1", "Goroka Airport", "-6.081689834590001", "145.391998291");
    airport airport2 = airport("2", "Madang Airport", "-5.20707988739", "145.789001465");
    airport airport3 = airport("6", "Narsarsuaq Airport", "61.1604995728", "-45.4259986877");
    airport airport4 = airport("207", "Blida Airport", "36.50360107421875", "2.8141698837280273");
    airport airport5 = airport("7437", "Inhaca Airport", "-25.9971446991", "32.929351806599996");

    //test random selection of combinations of above
    //hardcoded values were calculated using a haversine calculator website
    //Here we are checking to see if our calculated values are within 5 miles of the other value, to allow for some rounding error
    REQUIRE(abs(airport1.find_distance(airport2) - 66) < 5);
    REQUIRE(abs(airport2.find_distance(airport3) - 8525) < 5);
    REQUIRE(abs(airport2.find_distance(airport4) - 9246) < 5);
    REQUIRE(abs(airport2.find_distance(airport5) - 7456) < 5);
    REQUIRE(abs(airport3.find_distance(airport5) - 7408) < 5);
    cout << "Finished test get distance." << endl;
}

//###################
//BFS Tests
//###################

TEST_CASE("Check BFS")
{
    /*
       (0)            
  128 /   \ 290 
     /     \
   (1)     (2)
    The graph is this shape.
    */

    //Creates a random graph to check if BFS is correct or not
    Graph graph(true, 3, 1);

    //Calls in print method from BFS class
    BFS bfs;
    list<Vertex> bfsOrder = bfs.print("0", graph, BFS_output);
    

    //Few test cases to check BFS accuracy
    REQUIRE(bfsOrder.size() == 3);
    REQUIRE(bfsOrder.front() == "0");
    bfsOrder.pop_front();
    REQUIRE(bfsOrder.front() == "1");
    bfsOrder.pop_front();
    REQUIRE(bfsOrder.front() == "2");

    cout << "Finished test BFS." << endl;
}

//###################
//Dijkstra Tests
//###################

TEST_CASE("Check dijkstra algorithm for undirected graph")
{
    //Create a specific graph so we could know the algorithm actually works

    /*
       (2)
    5 /   \ 4 
     /     \
   (1)--9--(3)
    |      /|
    |    /  |
    7   2   2
    |  /    |
    |/      |
   (0)--0--(4)
     the graph is like this shape   
*/

    //test if it works for undirected graph

    Graph sample = Graph(true);
    sample.insertVertex("0");
    sample.insertVertex("1");
    sample.insertVertex("2");
    sample.insertVertex("3");
    sample.insertVertex("4");

    sample.insertEdge("2", "1");
    sample.insertEdge("2", "3");
    sample.insertEdge("1", "3");
    sample.insertEdge("1", "0");
    sample.insertEdge("0", "4");
    sample.insertEdge("4", "3");
    sample.insertEdge("0", "3");

    sample.setEdgeWeight("2", "1", 5);
    sample.setEdgeWeight("2", "3", 4);
    sample.setEdgeWeight("1", "3", 9);
    sample.setEdgeWeight("1", "0", 7);
    sample.setEdgeWeight("0", "4", 0);
    sample.setEdgeWeight("4", "3", 2);
    sample.setEdgeWeight("0", "3", 2);

    dijkstra shortest = dijkstra(sample, "0");

    REQUIRE(shortest.distance["1"] == 7);
    REQUIRE(shortest.distance["2"] == 6);
    REQUIRE(shortest.distance["3"] == 2);
    REQUIRE(shortest.distance["4"] == 0);

    cout << "Finished test dijkstra for undirected graph" << endl;
}

TEST_CASE("Check dijkstra algorithm for directed graph")
{
    Graph sample = Graph(true, true);

    sample.insertVertex("0");
    sample.insertVertex("1");
    sample.insertVertex("2");
    sample.insertVertex("3");
    sample.insertVertex("4");

    sample.insertEdge("2", "1");
    sample.insertEdge("3", "2");
    sample.insertEdge("1", "3");
    sample.insertEdge("1", "0");
    sample.insertEdge("0", "4");
    sample.insertEdge("4", "3");
    sample.insertEdge("0", "3");

    sample.setEdgeWeight("2", "1", 5);
    sample.setEdgeWeight("3", "2", 4);
    sample.setEdgeWeight("1", "3", 9);
    sample.setEdgeWeight("1", "0", 7);
    sample.setEdgeWeight("0", "4", 0);
    sample.setEdgeWeight("4", "3", 2);
    sample.setEdgeWeight("0", "3", 2);

    dijkstra shortest = dijkstra(sample, "0");

    REQUIRE(shortest.distance["1"] == 11);
    REQUIRE(shortest.distance["2"] == 6);
    REQUIRE(shortest.distance["3"] == 2);
    REQUIRE(shortest.distance["4"] == 0);

    cout << "Finished test dijkstra for directed graph." << endl;
}

//###################
//filehelper tests
//###################

TEST_CASE("Check good airports are read from file correctly")
{
    //read in minimal file with 5 good airports
    map<string, airport> airports = make_airports("tests/test_data/airports_minimal.dat");

    //check all 5 airports were added
    REQUIRE(airports.size() == 5);
    //check a couple airports to see they were correctly constructed
    REQUIRE(airports["1"].ID_ == "1");
    REQUIRE(airports["1"].name_ == "\"airport1\"");
    REQUIRE(airports["1"].latitude_ == "-10.000000000000001");
    REQUIRE(airports["1"].longitude_ == "5.000000001");

    REQUIRE(airports["2"].ID_ == "2");
    REQUIRE(airports["2"].name_ == "\"airport2\"");
    REQUIRE(airports["2"].latitude_ == "-5.000000000000001");
    REQUIRE(airports["2"].longitude_ == "10.000000001");

    cout << "Finished test good airports read from file." << endl;
}

TEST_CASE("Check airports with bad latitude and longitude aren't added")
{
    //this file has 3 bad airports and 2 good ones
    map<string, airport> airports = make_airports("tests/test_data/airports_minimal_bad.dat");
    REQUIRE(airports.size() == 2);

    cout << "Finished test bad airports ignored when read from file." << endl;
}

TEST_CASE("Check good routes are read from file and added correctly")
{
    //this file should have 14 good routes total between 5 airports
    map<string, vector<string>> routes = make_routes("tests/test_data/routes_minimal.dat");
    vector<string> v1{"3", "4", "5"};
    vector<string> v2{"3", "5"};
    vector<string> v3{"1", "2", "5"};
    vector<string> v4{"2", "5"};
    vector<string> v5{"1", "2", "3", "4"};

    REQUIRE(routes.size() == 5);
    REQUIRE(routes["1"] == v1);
    REQUIRE(routes["2"] == v2);
    REQUIRE(routes["3"] == v3);
    REQUIRE(routes["4"] == v4);
    REQUIRE(routes["5"] == v5);

    cout << "Finished test routes are read from file." << endl;
}

TEST_CASE("Check graph is made correctly from provided maps")
{
    map<string, airport> airports = make_airports("tests/test_data/airports_minimal.dat");
    map<string, vector<string>> routes = make_routes("tests/test_data/routes_minimal.dat");
    Graph graph = make_graph(airports, routes);

    REQUIRE(graph.getVertices().size() == 5);
    REQUIRE(graph.getEdges().size() == 14);
    REQUIRE(graph.edgeExists("1", "3"));
    REQUIRE(graph.edgeExists("1", "4"));
    REQUIRE(graph.edgeExists("1", "5"));
    REQUIRE(graph.edgeExists("2", "3"));
    REQUIRE(graph.edgeExists("2", "5"));
    REQUIRE(graph.edgeExists("3", "1"));
    REQUIRE(graph.edgeExists("3", "2"));
    REQUIRE(graph.edgeExists("3", "5"));
    REQUIRE(graph.edgeExists("4", "2"));
    REQUIRE(graph.edgeExists("4", "5"));
    REQUIRE(graph.edgeExists("5", "1"));
    REQUIRE(graph.edgeExists("5", "2"));
    REQUIRE(graph.edgeExists("5", "3"));
    REQUIRE(graph.edgeExists("5", "4"));

    cout << "Finished test graph is built correctly fron map inputs." << endl;
}

TEST_CASE("Check bad routes aren't added to graph")
{
    //the routes file should have 1 good route and 10 bad ones
    map<string, airport> airports = make_airports("tests/test_data/airports_minimal.dat");
    map<string, vector<string>> routes = make_routes("tests/test_data/routes_minimal_bad.dat");
    Graph graph = make_graph(airports, routes);

    REQUIRE(graph.getEdges().size() == 2);
    REQUIRE(graph.edgeExists("1", "2"));
    REQUIRE(graph.edgeExists("2", "3"));

    cout << "Finished test bad routes are ignored when read from file." << endl;
}

//###################
//landmark tests
//###################

TEST_CASE("Check landmark algorithm")
{
    //Using same graph from earlier testing with dijkstra
    Graph sample = Graph(true, true);

    sample.insertVertex("0");
    sample.insertVertex("1");
    sample.insertVertex("2");
    sample.insertVertex("3");
    sample.insertVertex("4");

    sample.insertEdge("2", "1");
    sample.insertEdge("3", "2");
    sample.insertEdge("1", "3");
    sample.insertEdge("1", "0");
    sample.insertEdge("0", "4");
    sample.insertEdge("4", "3");
    sample.insertEdge("0", "3");

    sample.setEdgeWeight("2", "1", 5);
    sample.setEdgeWeight("3", "2", 4);
    sample.setEdgeWeight("1", "3", 9);
    sample.setEdgeWeight("1", "0", 7);
    sample.setEdgeWeight("0", "4", 0);
    sample.setEdgeWeight("4", "3", 2);
    sample.setEdgeWeight("0", "3", 2);

    landmark l = landmark(sample, "2");

    //test various distances with 2 as the source
    REQUIRE(l.find_distance("3", "1") == 14);
    REQUIRE(l.find_distance("1", "3") == 23);
    REQUIRE(l.find_distance("4", "3") == 30);
    REQUIRE(l.find_distance("0", "1") == 12);
    REQUIRE(l.find_distance("0", "3") == 30);
    REQUIRE(l.find_distance("1", "4") == 23);
}