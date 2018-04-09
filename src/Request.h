#ifndef SRC_REQUEST_H_
#define SRC_REQUEST_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Time.h"
#include "Client.h"

class RideShare;

class Request {

public:

	Request();
	Request(RideShare * rideshare, Client * client,
			Time time, int requestStartPlace, int requestEndPlace,
			int simpleTime, int toleranceTime);

	Client * getClient() const;
	Time getRequestDepartureTime() const;
	int getRequestStartPlace() const;
	int getRequestEndPlace() const;
	int getSimpleTime() const;
	int getToleranceTime() const;
	int getUniqueRequestID() const;

	void setClient(Client * client);
	void setRequestStartPlace(int start);
	void setRequestEndPlace(int end);
	void setRequestDepartureTime(Time time);
	void setSimpleTime(int time);
	void setToleranceTime(int time);

	std::string showInfo() const;

private:

	RideShare * rideshare;
	Client * client;
	Time requestDepartureTime;
	int requestStartPlace;
	int requestEndPlace;
	int simpleTime;
	int toleranceTime;
	int uniqueRequestID;
	static int idRequest_provider;
};

#endif /* SRC_REQUEST_H_ */
