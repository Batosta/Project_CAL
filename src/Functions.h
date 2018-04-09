#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "Rideshare.h"
#include "graphviewer.h"
#include "edgetype.h"

void initialize();

void createRideShare();
void readClientsFile();
void readNodesFile();
void readEdgesFile();

void saveClientsFile();

void seeAllSomething(std::string str);
void findFastestRoute();
void findFastestRouteThroughPoints();
void showRouteMap(std::vector<int> path);

void createNewClient();
void createNewTravel();
void createNewRequest();

void deleteSomething(int number);

bool is_number(const std::string & s);
void openMap();
Time checkTime(std::string time);

#endif /* FUNCTIONS_H_ */
