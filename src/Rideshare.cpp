#ifndef RIDESHARE_CPP_
#define RIDESHARE_CPP_

#include "Rideshare.h"

using namespace std;

RideShare::RideShare() {

}
RideShare::RideShare(vector<Client *> clients, std::vector<Travel *> travels) {

	this->allTravels = travels;
}

vector<Client *> RideShare::getClients() const {

	return this->allClients;
}
vector<Travel *> RideShare::getTravels() const {

	return this->allTravels;
}
vector<Request *> RideShare::getRequests() const{

	return this->allRequests;
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
int RideShare::getIdByName(std::string str){
int i = 0;

	for	(auto it = this->getGraph().getVertexSet().begin(); it != this->getGraph().getVertexSet().end(); it++){

		if(i>1){
			if((*it)->getVertexName() == str){

				return (*it)->getInfo();
			}
		}
		i++;
	}
	return -1;
}

string RideShare::getNamebyId(int id){
int i = 0;

	for	(auto it = this->getGraph().getVertexSet().begin(); it != this->getGraph().getVertexSet().end(); it++){

		if(i>1){
			if((*it)->getInfo() == id){

				return (*it)->getVertexName();
			}
		}
		i++;
	}
	return "";
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

vector<string> RideShare::existsNodeName(string str){
	vector<string> v;
	int i = 0;
	cout << "cona1\n";
	for (auto it = this->graph.getVertexSet().begin();
			it != this->graph.getVertexSet().end(); it++) {
		cout << "cona2\n" << i;

		if (i > 1) {
			cout << "cona3 size:" << this->graph.getVertexSet().size() << endl;
			cout << (*it)->getVertexName() << endl;
			cout << (*it)->getInfo() << endl;
			cout << "cona3" << endl;
			if(kmpStringAlgorithm((*it)->getVertexName(), str)){

				v.push_back((*it)->getVertexName());
				cout << "vsize" << v.size() << endl;
			}
		}
		cout << i << endl;
		i++;
	}

	return v;
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
void RideShare::addNode(int ID, int x, int y, string name) {

	cout << "inside addnode. id: " << ID << "name:" << name << endl;
	this->graph.addVertex(ID, x, y, name);
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

		for (auto it = allTravels.begin(); it != allTravels.end();
			it++) {
			vector<string> placenames;

			for(auto ita = (*it)->getCurrentPath().begin() ; ita != (*it)->getCurrentPath().end();ita++){

			}

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

	cout << "\nTo go from: " << (*this->getGraph().getVertexSet().at(source+1)).getVertexName() << " to " << (*this->getGraph().getVertexSet().at(dest+1)).getVertexName()
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

		newTime.setHours(time.getHours() + tolerance % 60);
		newTime.setMinutes(time.getMinutes() + tolerance - (tolerance % 60)*60);
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

	return abs((time1.getHours() - time2.getHours()))*60 + (time1.getMinutes() - time2.getMinutes());
}

bool RideShare::kmpStringAlgorithm(const string total,const string partial) { //Algorithm for exact string search

	cout << "cona5" << endl;
	int m = partial.length();
	int n = total.length();
	int pi[m];

	computePrefixFunction(partial, pi);

	int i = 0;  // index for total[] string
	int j = 0;  // index for partial[] string
	while (i < n) {

		if (tolower(partial[j]) == tolower(total[i])){ //case insensitive    o codigo ASCII das minusculas é o das maiusculas + 32

			j++;
			i++;
		}

		if (j == m) {

			return true;
		}

		// mismatch after j matches
		else if (i < n && tolower(partial[j]) != tolower(total[i])) {
			if (j != 0)
				j = pi[j - 1];
			else
				i = i + 1;
		}
	}
	return false;
}

void RideShare::computePrefixFunction(string partial, int *pi) {

	int m = partial.length();
	// length of the previous longest prefix suffix
	int len = 0;

	pi[0] = 0; // lps[0] is always 0

	// the loop calculates lps[i] for i = 1 to M-1
	int i = 1;
	while (i < m) {
		if (tolower(partial[i]) == tolower(partial[len])) {
			len++;
			pi[i] = len;
			i++;
		} else // (pat[i] != pat[len])
		{
			// This is tricky. Consider the example.
			// AAACAAAA and i = 7. The idea is similar
			// to search step.
			if (len != 0) {
				len = pi[len - 1];

				// Also, note that we do not increment
				// i here
			} else // if (len == 0)
			{
				pi[i] = 0;
				i++;
			}
		}
	}
}


int RideShare::editDistanceAlgorithm(string pat, string txt){

	int n = txt.length();
	int m = pat.length();
	int after, before;
	int d[n+1];

	for (int i = 0; i < n + 1; i++) {

		d[i] = i;
	}

	for (int i = 1; i < m + 1; i++) {

		before = d[0];
		d[0] = i;

		for(int k = 1; k < n+1; k++){

			if(pat[i - 1] == txt[k - 1]){

				after = before;
			} else{

				after = min(before, d[k]);
				after = 1 + min(after, d[k-1]);
			}

			before = d[k];
			d[k] = after;
		}
	}

	return d[n];
}

#endif /* RIDESHARE_CPP_ */
