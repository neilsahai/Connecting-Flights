#include "airport.h"
#include "graph.h"
#include "BFS.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>

typedef string Vertex;

using namespace std;


list<Vertex> BFS::print(Vertex Source, Graph &graph, string Filename)
{   
    //Creates empty list to push all the vertices in bfs order
    list<Vertex> bfsOrder;

    //Creates a vector of vertices from our getVerticies method
    vector<Vertex> vertexVector = graph.getVertices();

    //Creates a map structure in order to keep track of visited vertices
    map<Vertex, bool> visited;

    //Loops though all the vertices and sets their values to false intially
    for (size_t i = 0; i < vertexVector.size(); i++)
    {
        visited[vertexVector[i]] = false;
    }

    //Create a queue to aid in BFS
    list<Vertex> queue;

    //Marks the Source node as visited and push it in the queue
    visited[Source] = true;
    queue.push_back(Source);

    //Create a ifstream object to redirct the output
    ofstream myfile;
    myfile.open(Filename);
    myfile << "The vertices traversed in BFS order are: " << endl;

    while (!queue.empty())
    {

        //Dequeue vertex and then prints it to the output file.
        //Pushes in vertex into list for testing purposes
        Source = queue.front();
        
        myfile << Source << ",";
        bfsOrder.push_back(Source);
        queue.pop_front();

        //Gets all the adjacent verticies from the dequeued vertex Source.
        //Checks to see if a adjacent has been visited or not.
        //If not visited then visits it and then enqueues it.
        for (auto it = graph.adjacency_list[Source].begin(); it != graph.adjacency_list[Source].end(); ++it)
        {
            if (visited[it->first] == false)
            {
                visited[it->first] = true;
                queue.push_back(it->first);
            }
        }
    }
    myfile.close();
    return bfsOrder;
}
