#ifndef RIDESHARE_CPP_
#define RIDESHARE_CPP_

#include "Rideshare.h"

using namespace std;

RideShare::RideShare() {

}
RideShare::RideShare(vector<Client *> clients, std::vector<Travel *> travels) {

	this->allClients = clients;
	this->allTravels = travels;
}

vector<Client *> RideShare::getClients() const {

	return this->allClients;
}
vector<Travel *> RideShare::getTravels() const {

	return this->allTravels;
}
Client * RideShare::getClientByID(int clientID) {

	for (auto it = allClients.begin(); it != allClients.end(); it++) {

		if ((*it)->getUniqueClientID() == clientID)
			return (*it);
	}
	return NULL;
}
Travel * RideShare::getTravelByID(int traveltID) {

	for (auto it = allTravels.begin(); it != allTravels.end(); it++) {

		if ((*it)->getUniqueTravelID() == traveltID)
			return (*it);
	}
	return NULL;
}

bool RideShare::existsClientID(int clientID) {

	for (auto it = allClients.begin(); it != allClients.end(); it++) {

		if ((*it)->getUniqueClientID() == clientID)
			return true;
	}
	return false;
}
bool RideShare::existsTravelID(int travelID) {

	for (auto it = allTravels.begin(); it != allTravels.end(); it++) {

		if ((*it)->getUniqueTravelID() == travelID)
			return true;
	}
	return false;
}
bool RideShare::existsNodeID(int nodeID) {

	int i = 0;
	for (auto it = this->graph.getVertexSet().begin();
			it != this->graph.getVertexSet().end(); it++) {

		if (i > 1) {
			if((*it)->getInfo() == nodeID)
				return true;
		}
		i++;
	}
	return false;
}

void RideShare::setClients(vector<Client *> clients) {

	allClients = clients;
}
void RideShare::setTravels(vector<Travel *> travels) {

	allTravels = travels;
}

void RideShare::addClient(Client * newClient) {

	this->allClients.push_back(newClient);
}
void RideShare::addTravel(Travel * newTravel) {

	this->allTravels.push_back(newTravel);
}
void RideShare::addNode(int ID, int x, int y) {

	this->graph.addVertex(ID, x, y);
}
void RideShare::addEdge(int originID, int destID, int direction) {

	if (direction == 0){
		this->graph.addEdge(originID, destID);
		this->graph.addEdge(destID, originID);
	}
	else
		this->graph.addEdge(originID, destID);
}

bool RideShare::removeClient(int uniqueID) {

	for (auto it = allClients.begin(); it != allClients.end(); it++) {

		if ((*it)->getUniqueClientID() == uniqueID) {

			allClients.erase(it);
			return true;
		}
	}
	return false;
}

bool RideShare::removeTravel(int uniqueID) {

	for (auto it = allTravels.begin(); it != allTravels.end(); it++) {

		if ((*it)->getUniqueTravelID() == uniqueID) {

			allTravels.erase(it);
			return true;
		}
	}
	return false;
}

string RideShare::showAllClients() {

	string allInfo = "";

	if (allClients.size() == 0) {

		allInfo = "There are no Clients to show.\n";
	} else {
		allInfo += "All Clients:\n";
		for (auto it = this->allClients.begin(); it != this->allClients.end();
				it++) {

			allInfo += (*it)->showInfo();
		}
	}
	return allInfo;
}

string RideShare::showAllTravels() {

	string allInfo = "";

	if (allTravels.size() == 0) {

		allInfo = "There are no Travels to show.\n";
	} else {
		allInfo += "All Travels:\n";
		for (auto it = this->allTravels.begin(); it != this->allTravels.end();
				it++) {
			allInfo += (*it)->showInfo();
		}
	}

	return allInfo;
}

void RideShare::showAllNodes() {

	if (graph.getNumVertex() == 0) {

		cout << "There are no Nodes to show.\n";
	} else {

		cout << "All Nodes:\n";
		int i = 0;
		for (auto it = this->graph.getVertexSet().begin();
				it != this->graph.getVertexSet().end(); it++) {

			if (i > 1) {
				(*it)->showVertexInfo();
			}
			i++;
		}
	}
}

void RideShare::showFastestRoute(int source, int dest){

	cout << "\nTo go from the node nº " << source << " to the node nº " << dest << ": ";

	this->graph.dijkstraShortestPath(source);
	vector<int> path = this->graph.getPath(source, dest);

	int totalDistance = 0;
	for(size_t t = 0; t < path.size(); t++){

		if(t != path.size() - 1)
			cout << path.at(t) << " -> ";
		else
			cout << path.at(t) << endl;

		for(auto it = this->graph.getVertexSet().begin(); it != this->graph.getVertexSet().end(); it++){

			if((*it)->getInfo() == path.at(t))
				totalDistance += (*it)->getDist();
		}
	}

	cout << "Distance: " << totalDistance/10.0 << " meters" << endl;
}

#endif /* RIDESHARE_CPP_ */
