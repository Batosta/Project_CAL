#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <limits.h>

#include "Rideshare.h"
#include "graphviewer.h"
#include "edgetype.h"

void initialize();

void createRideShare();
void readClientsFile();
void readNodesFile();
void readEdgesFile();
void readRequestsFile();
void readTravelsFile();

void saveClientsFile();
void saveRequestsFile();
void saveTravelsFile();

void seeAllSomething(std::string str);
void searchClientTravels(int id);
void findFastestRoute(int searchType);
void findFastestRouteThroughPoints(int searchType);
void showRouteMap(std::vector<int> path);

void createNewClient();
void createNewTravel(int searchType);
void createNewRequest();

void deleteSomething(int number);

bool is_number(const std::string & s);
void openMap();
Time checkTime(std::string time);
void manageAllTravels();
std::vector<int> bestPath(std::vector<int> sources, std::vector<int> dests);
std::vector<int> bestPathWithAllNodes(std::vector<int> path);


#endif /* FUNCTIONS_H_ */
