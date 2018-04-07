#include "Client.h"

#include <string>

using namespace std;

int Client::idClient_provider = 0;

//Constructors
Client::Client() {

	this->name = "";
}
Client::Client(RideShare * rideshare, string name, string phoneNumber) :
		uniqueClientID(++idClient_provider) {

	this->rideshare = rideshare;
	this->name = name;
	this->phoneNumber = phoneNumber;
}
Client::Client(RideShare * rideshare, string file_string) {

	// ID/name/phoneNumber/

	this->rideshare = rideshare;

	istringstream infoClient(file_string);

	string name, phoneNumber;
	int id;
	char garbage;

	infoClient >> id;

	this->uniqueClientID = id;

	infoClient >> garbage;

	getline(infoClient, name, '/');

	this->name = name;

	getline(infoClient, phoneNumber, '/');

	this->phoneNumber = phoneNumber;

	if (this->uniqueClientID > Client::idClient_provider)
		Client::idClient_provider = uniqueClientID;
}

//Get Methods
string Client::getName() const {

	return name;
}
int Client::getUniqueClientID() const {

	return uniqueClientID;
}

//Set Methods
void Client::setName(string name) {

	this->name = name;
}

//Other Methods
string Client::showInfo() const {

	string info = "";

	info += "Client nº " + std::to_string(this->uniqueClientID) + "\n"
			+ "\t -Name: " + this->name + "\n" + "\t -Phone Number: "
			+ this->phoneNumber + "\n";

	info += "\n";

	return info;

}

