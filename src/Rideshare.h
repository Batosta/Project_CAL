#ifndef RIDESHARE_H_
#define RIDESHARE_H_

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <queue>
#include <math.h>

#include "Travel.h"
#include "Client.h"
#include "Request.h"
#include "Graph.h"

class RideShare {

public:

	RideShare();
	RideShare(std::vector<Client *> clients, std::vector<Travel *> travels);

	std::vector<Client *> getClients() const;
	std::vector<Travel *> getTravels() const;
	std::vector<Request *> getRequests() const;
	Graph<int> getGraph() const;
	Client * getClientByID(int clientID);
	Travel * getTravelByID(int travelID);

	bool existsClientID(int clientID);
	bool existsTravelID(int travelID);
	bool existsNodeID(int nodeID);
	bool existsNodeName(std::string str);

	void setClients(std::vector<Client *> clients);
	void setTravels(std::vector<Travel *> travels);

	void addClient(Client * newClient);
	void addTravel(Travel * newTravel);
	void addRequest(Request * newRequest);
	void addNode(int ID, int x, int y, std::string name);
	void addEdge(int originID, int destID, int direction);

	bool removeClient(int uniqueID);
	bool removeTravel(int uniqueID);
	bool removeRequest(int uniqueID);

	std::string showAllClients();
	std::string showAllTravels();
	void showAllNodes();
	std::string showAllRequests();
	vector<int> getFastestRoute(int source, int dest);
	int getDistanceRoute(int source, int dest);
	int getSimpleTimeRoute(int source, int dest);

	void manageTravels();
	void clearVectors();

	Time addTimes(Time time, int tolerance);
	int differenceBetweenTimes(Time time1, Time time2);

	bool kmpStringAlgorithm(string total, string partial);
	void computePrefixFunction(string str, int m);

private:

	std::vector<Client *> allClients;
	std::vector<Travel *> allTravels;
	std::vector<Request *> allRequests;
	Graph<int> graph;
};

#endif /* RIDESHARE_H_ */
