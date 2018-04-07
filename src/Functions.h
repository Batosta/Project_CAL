#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

void initialize();

void createRideShare();
void readClientsFile();
void readNodesFile();
void readEdgesFile();

void seeAllSomething(std::string str);

void createNewClient();
void createNewTravel();

void deleteClient();
void deleteTravel();

bool is_number(const std::string & s);

void openMap();

#endif /* FUNCTIONS_H_ */
