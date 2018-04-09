#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <string>
#include <sstream>

class RideShare;

class Client{

public:

	Client();
	Client(RideShare * rideshare, std::string name, std::string phoneNumber);
	Client(RideShare * rideshare, std::string file_string);

	std::string getName() const;
	int getUniqueClientID() const;
	std::string getPhoneNumber() const;

	void setName(std::string name);

	std::string showInfo() const;

private:

	RideShare * rideshare;
	std::string name;
	std::string phoneNumber;
	int uniqueClientID;
	static int idClient_provider;
};

#endif /* CLIENT_H_ */
