# ferriss2-nsahai4-ytark2

Final Project Repository for cs225 Fall 2020

#### Contributers

* Daniel Ferriss ferriss2
* Neil Sahai nsahai4
* Youjin Tark ytark2 

#### Important links

* [Presentation Slides](https://docs.google.com/presentation/d/1lTdvEIz6chPQF7j36pBfM0VR8hoN38aMPcLyocgBEEI/edit?usp=sharing)
* [Presentation Video](https://www.youtube.com/watch?v=bun1VDv8cEs&feature=youtu.be)
* [Final Report Writeup](https://docs.google.com/document/d/1AUExayJ0g3H2vzPVdTERYvXrlrgppRA0luq2dehDvso/edit?usp=sharing)
* [Data Source](https://openflights.org/data.html)

### About The Project
This project leverages OpenFlights public routes and airports datasets to build a graph data structure containing all airports and routes. This allows us to find the shortest path between any airports, as well as the shortest path between two airports that intersects with a landmark airport.

### Data Requirements
Both files are comma delimited, with linebreaks being "\n". Fields cannot contain either of these characters.

##### airports.dat

Airport | Name | City | Country | IATA | ICAO | Latitude | Longitude | Altitude | Timezone | DST | Tz database time zone | Type | Source 
--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
Int | String | String | String | String | String | Float | Float | Int | Int | String | String | String | String | 

##### routes.dat

Airline | Airline ID | Source Airport | Source Aiport ID | Destination Airport | Destination Airport ID | Codeshare | Stops | Equipment
--------|--------|--------|--------|--------|--------|--------|--------|--------|
Int | Int | String | Int | String | Int | String | Int | String |

### Structure
Output files, including the single airport statistics file and the BFS traversal order are located in the output folder.

Data is located in the data folder

All documentation generated over the course of the project about what we were working on is in the documents folder

The graph is created from file by functions contained in file_helper.cpp. This file also contains the statistics file generator.

All headers and c++ files are in the folder root, save those used in testing.

### Running the project

The executable can be made with 'make' in the root of the project

This will generate an executable named 'cs225_project'

The test executable can be made with 'make test' in the root of the project

This will generate an executable named 'test'

The airport that is described in the statistics file can be configured in the main
