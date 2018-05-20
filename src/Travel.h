#ifndef TRAVEL_H_
#define TRAVEL_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Client.h"
#include "Time.h"
#include "Request.h"

class RideShare;

class Travel {

public:

	Travel();
	Travel(RideShare * rideshare, int availableSeats, Client * driver,
			Time time, int tolerance, int simpleTime, int travelStartPlace, int travelEndPlace, std::vector<int> path);

	Client * getTravelDriver() const;
	std::vector<Request *> getAllRequests() const;
	std::vector<Client *> getAllClientsGoing() const;
	std::vector<int> getAllSources() const;
	std::vector<int> getAllDests() const;
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
	void setAllSources(std::vector<int> sources);
	void setAllDests(std::vector<int> dests);
	void setAvailableSeats(int seats);
	void setTravelStartPlace(int start);
	void setTravelEndPlace(int end);
	void setTravelDepartureTime(Time time);
	void setToleranceTime(int time);
	void setSimpleTime(int time);
	void setOriginalPath(std::vector<int> path);
	void setCurrentPath(std::vector<int> path);

	bool searchClient(std::string str);


	void addClient(Client * client);
	void addRequest(Request * request);
	void addSource(int source);
	void addDest(int dest);
	std::string showInfo() const;

private:

	RideShare * rideshare;
	Client * driver;
	std::vector<Client *> allClientsGoing;
	std::vector<Request *> allRequests;
	std::vector<int> sources;
	std::vector<int> dests;
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
