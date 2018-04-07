#include "Travel.h"

#include <string>

using namespace std;

int Travel::idTravel_provider = 0;

//Constructors
Travel::Travel() {

}
Travel::Travel(RideShare * rideShare, int availableSeats, Client * driver,
		std::string travelDepartureTime, std::string travelStartPlace,
		std::string travelEndPlace) :
		uniqueTravelID(++idTravel_provider) {

	this->rideshare = rideShare;
	this->availableSeats = availableSeats;
	this->driver = driver;
	vector<Client *> clients;
	this->allClientsGoing = clients;
	this->travelDepartureTime = travelDepartureTime;
	this->travelStartPlace = travelStartPlace;
	this->travelEndPlace = travelEndPlace;
	this->travelDistance = 0.0;
}

//Get Methods
int Travel::getAvailableSeats() const {

	return this->availableSeats;
}
string Travel::getTravelDepartureTime() const {

	return this->travelDepartureTime;
}
string Travel::getTravelStartPlace() const {

	return this->travelStartPlace;
}
string Travel::getTravelEndPlace() const {

	return this->travelEndPlace;
}
float Travel::getTravelDistance() const {

	return 0.0;
}
float Travel::getTravelEstimatedTime() const {

	float averageSpeed = 25.0;
	return this->travelDistance / averageSpeed;
}
int Travel::getUniqueTravelID() const {

	return this->uniqueTravelID;
}
Client * Travel::getTravelDriver() const {

	return this->driver;
}
std::vector<Client *> Travel::getAllClientsGoing() const {

	return this->allClientsGoing;
}

//Set Methods
void Travel::setAvailableSeats(int seats) {

	this->availableSeats = seats;
}
void Travel::setTravelDriver(Client * driver) {

	this->driver = driver;
}
void Travel::setAllClientsGoing(std::vector<Client *> clients) {

	this->allClientsGoing = clients;
}
void Travel::setTravelDepartureTime(string departureTime) {

	this->travelDepartureTime = departureTime;
}
void Travel::setTravelStartPlace(std::string start) {

	this->travelStartPlace = start;
}
void Travel::setTravelEndPlace(std::string end) {

	this->travelEndPlace = end;
}
void Travel::setTravelDistance(float distance) {

	this->travelDistance = distance;
}

//Other Methods
string Travel::showInfo() const {

	string info = "";

	info += "Travel nº " + std::to_string(this->uniqueTravelID) + ":\n"
			+ "\t -Driver: " + this->driver->getName() + "\n"
			+ "\t -Departure Time: " + this->travelDepartureTime + "\n"
			+ "\t -Estimate Time: "
			+ std::to_string(this->getTravelEstimatedTime()) + "\n"
			+ "\t -Start Point: " + this->travelStartPlace + "\n"
			+ "\t -End Point: " + this->travelEndPlace + "\n" + "\t -Distance: "
			+ std::to_string(this->travelDistance) + "\n"
			+ "\t -Available Seats: " + std::to_string(this->availableSeats)
			+ "\n" + "\t -Clients Traveling: ";

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
	info += "\n";

	return info;
}

