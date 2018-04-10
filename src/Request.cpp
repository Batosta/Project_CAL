#include "Request.h"

#include <string>

using namespace std;

class RideShare;

int Request::idRequest_provider = 0;

//Constructors
Request::Request() {

}
Request::Request(RideShare * rideshare, Client * client, Time time,
		int requestStartPlace, int requestEndPlace, int simpleTime,
		int toleranceTime) :
		uniqueRequestID(++idRequest_provider) {

	this->rideshare = rideshare;
	this->client = client;
	this->requestDepartureTime = time;
	this->requestStartPlace = requestStartPlace;
	this->requestEndPlace = requestEndPlace;
	this->simpleTime = simpleTime;
	this->toleranceTime = toleranceTime;
}

//Get Methods
Client * Request::getClient() const {

	return this->client;
}
Time Request::getRequestDepartureTime() const {

	return this->requestDepartureTime;
}
int Request::getRequestStartPlace() const {

	return this->requestStartPlace;
}
int Request::getRequestEndPlace() const {

	return this->requestEndPlace;
}
int Request::getSimpleTime() const {

	return this->simpleTime;
}
int Request::getToleranceTime() const {

	return this->toleranceTime;
}
int Request::getUniqueRequestID() const {

	return this->uniqueRequestID;
}

//Set Methods
void Request::setClient(Client * client) {

	this->client = client;
}
void Request::setRequestStartPlace(int start) {

	this->requestStartPlace = start;
}
void Request::setRequestEndPlace(int end) {

	this->requestEndPlace = end;
}
void Request::setRequestDepartureTime(Time time) {

	this->requestDepartureTime = time;
}
void Request::setSimpleTime(int time) {

	this->simpleTime = time;
}
void Request::setToleranceTime(int time) {

	this->toleranceTime = time;
}

string Request::showInfo() const {

	string info = "";

	info += "Request nº " + to_string(this->uniqueRequestID) + "\n"
			+ "\t -Client Name: " + this->client->getName() + "\n"
			+ "\t -Expected Departure Time: ";

	if (requestDepartureTime.getHours() < 10)
		info += "0";

	info += to_string(this->requestDepartureTime.getHours()) + ":";

	if (this->requestDepartureTime.getMinutes() < 10)
		info += "0";

	info += to_string(this->requestDepartureTime.getMinutes()) + "\n"
			+ "\t -Starting Node: " + to_string(this->requestStartPlace)
			+ "\n" + "\t -Finishing Node: "
			+ to_string(this->requestEndPlace) + "\n"
			+ "\t -Minimum Travel Time: " + to_string(this->simpleTime)
			+ "\n" + "\t -Maximum Late Tolerance: "
			+ to_string(this->toleranceTime) + "\n"
			+ "\t -Expected Travel Time: " + to_string(this->simpleTime)
			+ "\n";

	info += "\n";

	return info;
}
