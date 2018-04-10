#ifndef TRAVEL_H_
#define TRAVEL_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Client.h"
#include "Time.h"

class RideShare;

class Travel {

public:

	Travel();
	Travel(RideShare * rideshare, int availableSeats, Client * driver,
			Time time, int tolerance, int travelStartPlace, int travelEndPlace, int simpleTime, std::vector<int> path);

	Client * getTravelDriver() const;
	std::vector<Client *> getAllClientsGoing() const;
	int getAvailableSeats() const;
	Time getTravelDepartureTime() const;
	int getTravelStartPlace() const;
	int getTravelEndPlace() const;
	int getToleranceTime() const;
	int getSimpleTime() const;
	std::vector<int> getOriginalPath() const;
	std::vector<int> getCurrentPath() const;
	int getUniqueTravelID() const;

	void setTravelDriver(Client * driver);
	void setAllClientsGoing(std::vector<Client *> clients);
	void setAvailableSeats(int seats);
	void setTravelStartPlace(int start);
	void setTravelEndPlace(int end);
	void setTravelDepartureTime(Time time);
	void setToleranceTime(int time);
	void setSimpleTime(int time);
	void setOriginalPath(std::vector<int> path);
	void setCurrentPath(std::vector<int> path);

	std::string showInfo() const;

private:

	RideShare * rideshare;
	Client * driver;
	std::vector<Client *> allClientsGoing;
	std::vector<int> originalPath;
	std::vector<int> currentPath;
	int availableSeats;
	Time travelDepartureTime;
	int travelStartPlace;
	int travelEndPlace;
	int toleranceTime;
	int simpleTime;
	int uniqueTravelID;
	static int idTravel_provider;
};

#endif /* TRAVEL_H_ */
