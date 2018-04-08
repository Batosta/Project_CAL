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
#include "Graph.h"


class RideShare {

public:

	RideShare();
	RideShare(std::vector<Client *> clients, std::vector<Travel *> travels);

	std::vector<Client *> getClients() const;
	std::vector<Travel *> getTravels() const;
	Client * getClientByID(int clientID);
	Travel * getTravelByID(int travelID);

	bool existsClientID(int clientID);
	bool existsTravelID(int travelID);
	bool existsNodeID(int nodeID);

	void setClients(std::vector<Client *> clients);
	void setTravels(std::vector<Travel *> travels);

	void addClient(Client * newClient);
	void addTravel(Travel * newTravel);
	void addNode(int ID, int x, int y);
	void addEdge(int originID, int destID, int direction);

	bool removeClient(int uniqueID);
	bool removeTravel(int uniqueID);

	std::string showAllClients();
	std::string showAllTravels();
	void showAllNodes();
	void showFastestRoute(int source, int dest);

private:

	std::vector<Client *> allClients;
	std::vector<Travel *> allTravels;
	Graph<int> graph;
};

#endif /* RIDESHARE_H_ */
