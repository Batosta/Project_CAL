#include "Travel.h"

#include <string>

using namespace std;

int Travel::idTravel_provider = 0;

//Constructors
Travel::Travel() {

}
Travel::Travel(RideShare * rideShare, int availableSeats, Client * driver,
		Time time, int tolerance, int simpleTime, int travelStartPlace,
		int travelEndPlace, vector<int> path) :
		uniqueTravelID(++idTravel_provider) {

	this->rideshare = rideShare;
	this->availableSeats = availableSeats;
	this->driver = driver;
	vector<Client *> clients;
	this->allClientsGoing = clients;
	vector<int> sources;
	this->sources = sources;
	vector<int> dests;
	this->dests = dests;
	this->travelDepartureTime = time;
	this->toleranceTime = tolerance;
	this->simpleTime = simpleTime;
	this->travelStartPlace = travelStartPlace;
	this->travelEndPlace = travelEndPlace;
	this->originalPath = path;
	this->currentPath = path;
}

//Get Methods
int Travel::getAvailableSeats() const {

	return this->availableSeats;
}
Time Travel::getTravelDepartureTime() const {

	return this->travelDepartureTime;
}
int Travel::getTravelStartPlace() const {

	return this->travelStartPlace;
}
int Travel::getTravelEndPlace() const {

	return this->travelEndPlace;
}
Client * Travel::getTravelDriver() const {

	return this->driver;
}
vector<Client *> Travel::getAllClientsGoing() const {

	return this->allClientsGoing;
}
vector<int> Travel::getAllSources() const {

	return this->sources;
}
vector<int> Travel::getAllDests() const {

	return this->dests;
}
int Travel::getToleranceTime() const {

	return this->toleranceTime;
}
int Travel::getUniqueTravelID() const {

	return this->uniqueTravelID;
}
int Travel::getSimpleTime() const {

	return this->simpleTime;
}
vector<int> Travel::getOriginalPath() const {

	return this->originalPath;
}
vector<int> Travel::getCurrentPath() const {

	return this->currentPath;
}

//Set Methods
void Travel::setAvailableSeats(int seats) {

	this->availableSeats = seats;
}
void Travel::setTravelDriver(Client * driver) {

	this->driver = driver;
}
void Travel::setAllClientsGoing(vector<Client *> clients) {

	this->allClientsGoing = clients;
}
void Travel::setAllSources(vector<int> sources) {

	this->sources = sources;
}
void Travel::setAllDests(vector<int> dests) {

	this->dests = dests;
}
void Travel::setTravelDepartureTime(Time time) {

	this->travelDepartureTime = time;
}
void Travel::setTravelStartPlace(int start) {

	this->travelStartPlace = start;
}
void Travel::setTravelEndPlace(int end) {

	this->travelEndPlace = end;
}
void Travel::setToleranceTime(int time) {

	this->toleranceTime = time;
}
void Travel::setSimpleTime(int time) {

	this->simpleTime = time;
}
void Travel::setOriginalPath(vector<int> path) {

	this->originalPath = path;
}
void Travel::setCurrentPath(vector<int> path) {

	this->currentPath = path;
}

void Travel::addClient(Client * client){

	this->allClientsGoing.push_back(client);
}

void Travel::addSource(int source){

	this->sources.push_back(source);
}
void Travel::addDest(int dest){

	this->dests.push_back(dest);
}

//Other Methods
string Travel::showInfo() const {

	string info = "";

	info += "Travel nº " + to_string(this->uniqueTravelID) + ":\n"
			+ "\t -Driver: " + this->driver->getName() + "\n"
			+ "\t -Departure Time: ";

	if (travelDepartureTime.getHours() < 10)
		info += "0";

	info += to_string(this->travelDepartureTime.getHours()) + ":";

	if (travelDepartureTime.getMinutes() < 10)
		info += "0";

	info += to_string(this->travelDepartureTime.getMinutes()) + "\n"
			+ "\t -Tolerance Time: " + to_string(this->toleranceTime) + "\n"
			+ "\t -Start Point: " + to_string(this->travelStartPlace) + "\n"
			+ "\t -End Point: " + to_string(this->travelEndPlace) + "\n"
			+ "\t -Available Seats: " + to_string(this->allClientsGoing.size())
			+ "/" + to_string(this->availableSeats) + "\n"
			+ "\t -Clients Traveling: ";

	if (allClientsGoing.size() == 0) {

		info += "No Clients traveling yet\n";
	}
	for (size_t t = 0; t < this->allClientsGoing.size(); t++) {

		if (t == (this->allClientsGoing.size() - 1)) {
			info += this->allClientsGoing.at(t)->getName();
			break;
		}
		info += this->allClientsGoing.at(t)->getName() + ", ";

	}

	info += "\n\t -Path Nodes: ";
	for (size_t t = 0; t < this->getCurrentPath().size(); t++) {

		if (t == (this->getCurrentPath().size() - 1)) {
			info += to_string(this->getCurrentPath().at(t));
			break;
		}
		info += to_string(this->getCurrentPath().at(t)) + ", ";
	}

	info += "\n";

	return info;
}

