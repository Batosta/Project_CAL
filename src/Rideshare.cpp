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
Graph<int> RideShare::getGraph() const {

	return this->graph;
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
			if ((*it)->getInfo() == nodeID)
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
void RideShare::addRequest(Request * newRequest) {

	this->allRequests.push_back(newRequest);
}
void RideShare::addNode(int ID, int x, int y) {

	this->graph.addVertex(ID, x, y);
}
void RideShare::addEdge(int originID, int destID, int direction) {

	if (direction == 0) {
		this->graph.addEdge(originID, destID);
		this->graph.addEdge(destID, originID);
	} else
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

bool RideShare::removeRequest(int uniqueID) {

	for (auto it = allRequests.begin(); it != allRequests.end(); it++) {

		if ((*it)->getUniqueRequestID() == uniqueID) {

			allRequests.erase(it);
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

string RideShare::showAllRequests() {

	string allInfo = "";

	if (allRequests.size() == 0) {

		allInfo = "There are no Requests to show.\n";
	} else {
		allInfo += "All Requests:\n";
		for (auto it = this->allRequests.begin(); it != this->allRequests.end();
				it++) {
			allInfo += (*it)->showInfo();
		}
	}

	return allInfo;
}

int RideShare::getSimpleTimeRoute(int source, int dest) {

	return getDistanceRoute(source, dest) / 70.0;
}
int RideShare::getDistanceRoute(int source, int dest) {

	double distance = 0;
	this->graph.dijkstraShortestPath(source);
	vector<int> path = this->graph.getPath(source, dest);

	for (size_t t = 0; t < path.size() - 1; t++) {

		distance += this->graph.calculateEdgeWeight(path.at(t), path.at(t + 1));
	}
	return distance;
}
vector<int> RideShare::getFastestRoute(int source, int dest) {

	cout << "\nTo go from the node nº " << source << " to the node nº " << dest
			<< ": ";

	this->graph.dijkstraShortestPath(source);
	vector<int> path = this->graph.getPath(source, dest);

	double totalDistance = 0;
	for (size_t t = 0; t < path.size(); t++) {

		if (t != path.size() - 1){
			cout << path.at(t) << " -> ";
			totalDistance += this->graph.calculateEdgeWeight(path.at(t),
					path.at(t + 1));
		}
		else
			cout << path.at(t) << endl;
	}

	cout << "Distance: " << totalDistance << " meters" << endl;
	cout << "Time: " << round(totalDistance / 70.0) << " minutes" << endl;
	return path;
}

void RideShare::manageTravels() {

	clearVectors();

	for (auto itr = this->allRequests.begin(); itr != this->allRequests.end();
			itr++) {

		for (auto itt = this->allTravels.begin(); itt != this->allTravels.end();
				itt++) {

			if ((*itt)->getAvailableSeats()
					<= (*itt)->getAllClientsGoing().size())	//no more available seats
				continue;

			this->graph.dijkstraShortestPath((*itt)->getTravelStartPlace());
			vector<int> path1 = this->graph.getPath(
					(*itt)->getTravelStartPlace(),
					(*itr)->getRequestStartPlace());
			int totalWaitingTime = 0;
			for (size_t t = 0; t < path1.size() - 1; t++) {

				totalWaitingTime += this->graph.calculateEdgeWeight(path1.at(t), path1.at(t + 1));
			}
			totalWaitingTime /= 70.0;
			cout << "Waiting Time: " << totalWaitingTime;

			this->graph.dijkstraShortestPath((*itr)->getRequestStartPlace());
			vector<int> path2 = this->graph.getPath(
					(*itr)->getRequestStartPlace(),
					(*itr)->getRequestEndPlace());

			this->graph.dijkstraShortestPath((*itr)->getRequestEndPlace());
			vector<int> path3 = this->graph.getPath(
					(*itr)->getRequestEndPlace(), (*itt)->getTravelEndPlace());


			vector<int> fullPath;
			for (size_t t = 0; t < path1.size(); t++) {
				fullPath.push_back(path1.at(t));
			}
			for (size_t t = 1; t < path2.size(); t++) {
				fullPath.push_back(path2.at(t));
			}
			for (size_t t = 1; t < path3.size(); t++) {
				fullPath.push_back(path3.at(t));
			}

			int totalTravelMinutes = 0;
			for (size_t t = 0; t < fullPath.size() - 1; t++) {

				totalTravelMinutes += this->graph.calculateEdgeWeight(
						fullPath.at(t), fullPath.at(t + 1));
			}
			totalTravelMinutes /= 70.0;				//tempo da viagem total (min)
			cout << "\ntotalTravelMinutes: " << totalTravelMinutes;


			Time finishSimpleTime = addTimes((*itt)->getTravelDepartureTime(), (*itt)->getSimpleTime());
			cout << "\nHora que acabaria: " << finishSimpleTime.getHours() << ":" << finishSimpleTime.getMinutes();


			Time finishFullTime;
			//travel quer sair antes do request (traveler espera pelo requester = tolerancia do traveler)
			if (((*itt)->getTravelDepartureTime().getHours() == (*itr)->getRequestDepartureTime().getHours()
					&& (*itt)->getTravelDepartureTime().getMinutes() < (*itr)->getRequestDepartureTime().getMinutes())
					|| (*itt)->getTravelDepartureTime().getHours() < (*itr)->getRequestDepartureTime().getHours()) {

				cout << "\nA";
				finishFullTime = addTimes((*itr)->getRequestDepartureTime(), totalTravelMinutes);
				cout << " Hora que acaba: " << finishFullTime.getHours() << ":" << finishFullTime.getMinutes();
			}
			//mesma hora OU travel depois do request (requester espera pelo traveler = tolerancia do requester)
			else {

				cout << "\nB";
				finishFullTime = addTimes((*itt)->getTravelDepartureTime(), totalTravelMinutes);
				cout << " Hora que acaba: " << finishFullTime.getHours() << ":" << finishFullTime.getMinutes();
			}

			cout << "\ndifference: " << differenceBetweenTimes(finishFullTime, finishSimpleTime);
			cout << "\ntolerance: " << (*itt)->getToleranceTime();

			if (differenceBetweenTimes(finishFullTime, finishSimpleTime) > (*itt)->getToleranceTime())
				continue;

			cout << "\ntolerance2: " << (*itr)->getToleranceTime();
			if (totalWaitingTime > (*itr)->getToleranceTime())
				continue;

			(*itt)->addClient((*itr)->getClient());
			(*itt)->setCurrentPath(fullPath);
			cout << "Added Client nº "
					<< (*itr)->getClient()->getUniqueClientID() << " - "
					<< (*itr)->getClient()->getName() << " to this travel.";
		}
	}
}

void RideShare::clearVectors() {

	vector<Client *> clients;
	for (auto it = this->allTravels.begin(); it != this->allTravels.end();
			it++) {
		(*it)->setAllClientsGoing(clients);
		(*it)->setCurrentPath((*it)->getOriginalPath());
	}
}

Time RideShare::addTimes(Time time, int tolerance) {

	Time newTime;
	if ((time.getMinutes() + tolerance) >= 60) {

		newTime.setHours(time.getHours() + 1);
		newTime.setMinutes(time.getMinutes() - 60 + tolerance);
	} else {

		newTime.setHours(time.getHours());
		newTime.setMinutes(time.getMinutes() + tolerance);
	}

	if (newTime.getHours() >= 24) {
		newTime.setHours(0);
	}

	return newTime;
}

int RideShare::differenceBetweenTimes(Time time1, Time time2) {

	if (time1.getHours() == time2.getHours()) {

		return time1.getMinutes() - time2.getMinutes();
	} else {

		return 60 - (time2.getMinutes() - time1.getMinutes());
	}
}
#endif /* RIDESHARE_CPP_ */
