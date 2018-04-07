#ifndef TRAVEL_H_
#define TRAVEL_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Client.h"

class RideShare;

class Travel {

public:

	Travel();
	Travel(RideShare * rideshare, int availableSeats, Client * driver,
			std::string travelDepartureTime, std::string travelStartPlace,
			std::string travelEndPlace);

	Client * getTravelDriver() const;
	std::vector<Client *> getAllClientsGoing() const;
	int getAvailableSeats() const;
	std::string getTravelDepartureTime() const;
	std::string getTravelStartPlace() const;
	std::string getTravelEndPlace() const;
	float getTravelDistance() const;
	float getTravelEstimatedTime() const;
	int getUniqueTravelID() const;

	void setTravelDriver(Client * driver);
	void setAllClientsGoing(std::vector<Client *> clients);
	void setAvailableSeats(int seats);
	void setTravelStartPlace(std::string start);
	void setTravelEndPlace(std::string end);
	void setTravelDepartureTime(std::string departureTime);
	void setTravelDistance(float distance);

	std::string showInfo() const;

private:

	RideShare * rideshare;
	Client * driver;
	std::vector<Client *> allClientsGoing;
	//std::vector<Place *> allPlacesClientsGoing;
	int availableSeats;
	std::string travelDepartureTime;
	std::string travelStartPlace;
	std::string travelEndPlace;
	float travelDistance;
	int uniqueTravelID;
	static int idTravel_provider;
};

#endif /* TRAVEL_H_ */
