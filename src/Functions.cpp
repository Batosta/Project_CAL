#include "Functions.h"

using namespace std;

RideShare * rideShare;
GraphViewer * gv;

void initialize() {

	openMap();
	createRideShare();
	readClientsFile();
	readNodesFile();
	readEdgesFile();
}

void readClientsFile() {

	ifstream file;
	string line;
	file.open("docs/clients.txt");
	while (getline(file, line)) {

		Client * newClient = new Client(rideShare, line);
		rideShare->addClient(newClient);
	}
	file.close();
}

void readNodesFile() {

	ifstream file;
	string line;
	file.open("docs/nodes.txt");

	while (getline(file, line)) {

		//nodeId;xCoordinate;yCoordinate;

		istringstream infoNode(line);

		int nodeID, xCoordinate, yCoordinate;
		char garbage;

		infoNode >> nodeID;
		infoNode >> garbage;

		infoNode >> xCoordinate;
		infoNode >> garbage;

		infoNode >> yCoordinate;
		infoNode >> garbage;

		gv->addNode(nodeID, xCoordinate, yCoordinate);
		gv->setVertexLabel(nodeID, to_string(nodeID));
		rideShare->addNode(nodeID, xCoordinate, yCoordinate); //colocar todos os Vertex no vertexSet do Graph
	}
	file.close();
}

void readEdgesFile() {

	ifstream file;
	string line;
	file.open("docs/roads.txt");
	while (getline(file, line)) {

		//roadID;nodeID1;nodeID2;true/false;"roadName";
		//true ou false indica se tem 1/2 direcoes

		istringstream infoEdge(line);

		int roadID, nodeID1, nodeID2;
		string directions; //(true/false)
		string roadName;
		char garbage;

		infoEdge >> roadID;
		infoEdge >> garbage;

		infoEdge >> nodeID1;
		infoEdge >> garbage;

		infoEdge >> nodeID2;
		infoEdge >> garbage;

		getline(infoEdge, directions, ';');

		getline(infoEdge, roadName, ';');

		//										0 = UNDIRECTED			1 = DIRECTED
		if (directions == "true") {

			rideShare->addEdge(nodeID2, nodeID1, EdgeType::UNDIRECTED);
			gv->addEdge(roadID, nodeID1, nodeID2, EdgeType::UNDIRECTED);
		} else {

			rideShare->addEdge(nodeID1, nodeID2, EdgeType::DIRECTED);
			gv->addEdge(roadID, nodeID1, nodeID2, EdgeType::DIRECTED);
		}

		gv->setEdgeLabel(roadID, roadName);
	}
	file.close();
}

void readRequestsFile(){

}
void readTravelsFile(){

}
void saveRequestsFile(){

}
void saveTravelsFile(){

}

void saveClientsFile() {

	ofstream file("docs/clients.txt");

	vector<Client *> clientsVector;

	for (Client * elem : rideShare->getClients()) {
		clientsVector.push_back(elem);
	}

	for (size_t i = 0; i < clientsVector.size(); i++) {
		file << clientsVector.at(i)->getUniqueClientID() << "/";
		file << clientsVector.at(i)->getName() << "/";
		file << clientsVector.at(i)->getPhoneNumber() << "/";

		if (i != clientsVector.size() - 1)
			file << endl;
	}
	file.close();
}

void seeAllSomething(string str) {

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;

	int i;
	if (str == "clients")
		i = 0;
	else if (str == "travels")
		i = 1;
	else if (str == "nodes")
		i = 2;
	else
		i = 3;

	string output = "";
	switch (i) {

	case 0:
		output = rideShare->showAllClients();
		break;
	case 1:
		output = rideShare->showAllTravels();
		break;
	case 2:
		rideShare->showAllNodes();
		break;
	case 3:
		output = rideShare->showAllRequests();
		break;
	}

	cout << output;
}

void findFastestRoute() {

	string tempID;
	int sourceID, destID;

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Insert the ID of the source node: ";
	getline(cin, tempID);
	if (!is_number(tempID)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	sourceID = stoi(tempID);
	if (!rideShare->existsNodeID(sourceID)) {
		cout << "\nThere is no Node with the ID: " << sourceID << endl;
		return;
	}

	cout << "Insert the ID of the destiny node: ";
	getline(cin, tempID);
	if (!is_number(tempID)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	destID = stoi(tempID);
	if (destID == sourceID) {
		cout << "\nThe source and destiny ID can not be the same. " << endl;
		return;
	}
	if (!rideShare->existsNodeID(destID)) {
		cout << "\nThere is no Node with the ID: " << destID << endl;
		return;
	}

	vector<int> path = rideShare->getFastestRoute(sourceID, destID);
	showRouteMap(path);
}
void findFastestRouteThroughPoints() {

	string tempNumber;
	int sourceID, destID, numberPoints, middlePointID;
	vector<int> middlePoints;

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Insert the ID of the source node: ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	sourceID = stoi(tempNumber);
	if (!rideShare->existsNodeID(sourceID)) {
		cout << "\nThere is no Node with the ID: " << sourceID << endl;
		return;
	}
	middlePoints.push_back(sourceID);

	cout << "Insert the number of middle points: ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	numberPoints = stoi(tempNumber);
	if (numberPoints <= 0 || numberPoints > 5) {
		cout << "\nThe number must be above 0 and below 5";
		return;
	}
	for (int i = 0; i < numberPoints; i++) {

		cout << "Insert the ID of the next node: ";
		getline(cin, tempNumber);
		if (!is_number(tempNumber)) {
			cout << "Not an integer.\n" << endl;
			return;
		}
		middlePointID = stoi(tempNumber);
		if (!rideShare->existsNodeID(middlePointID)) {
			cout << "\nThere is no Node with the ID: " << middlePointID << endl;
			return;
		}
		middlePoints.push_back(middlePointID);
	}

	cout << "Insert the ID of the destiny node: ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	destID = stoi(tempNumber);
	if (destID == sourceID) {
		cout << "\nThe source and destiny ID can not be the same. " << endl;
		return;
	}
	if (!rideShare->existsNodeID(destID)) {
		cout << "\nThere is no Node with the ID: " << destID << endl;
		return;
	}
	middlePoints.push_back(destID);

	vector<int> completePath;
	vector<int> tempPath;
	completePath.push_back(sourceID);
	for (size_t t = 0; t < middlePoints.size() - 1; t++) {

		tempPath = rideShare->getFastestRoute(middlePoints.at(t),
				middlePoints.at(t + 1));
		for (size_t t = 1; t < tempPath.size(); t++) {

			completePath.push_back(tempPath.at(t));
		}
	}
}
void showRouteMap(vector<int> path) {

	gv = new GraphViewer(600, 600, false);
	gv->defineVertexColor("yellow");
	gv->defineEdgeColor("black");
	gv->setBackground("docs/vilareal.png");
	gv->defineEdgeCurved(false);
	gv->createWindow(767, 792);

	for (size_t t = 0; t < path.size(); t++) {

		for (auto it = rideShare->getGraph().getVertexSet().begin();
				it != rideShare->getGraph().getVertexSet().end(); it++) {

			if ((*it)->getInfo() == path.at(t)) {

				gv->addNode(path.at(t), (*it)->getXCoordinate(),
						(*it)->getYCoordinate());

				if (t != 0)
					gv->addEdge(t, path.at(t - 1), path.at(t),
							EdgeType::DIRECTED);

				break;
			}
		}
		sleep(1);
		gv->rearrange();
	}
}

void createRideShare() {

	vector<Client *> clients;
	vector<Travel *> travels;
	rideShare = new RideShare(clients, travels);
}

void createNewClient() {

	string name, phoneNumber;

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Insert the name of the new Client: ";
	getline(cin, name);
	cout << "Insert the phone number of the new Client: ";
	getline(cin, phoneNumber);

	Client * newClient = new Client(rideShare, name, phoneNumber);
	rideShare->addClient(newClient);
	cout << "\nClient added with success!" << endl << endl;

	sleep(1);
}
void createNewTravel() {

	int driverID, seats, startPlace, endPlace, tolerance;
	string tempNumber;
	string departureTime;

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Insert the ID of the Client who is driving: ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	driverID = stoi(tempNumber);
	if (!rideShare->existsClientID(driverID)) {
		cout << "\nThere is no Client with the ID: " << driverID << endl;
		return;
	}

	cout << "Insert the number of available seats: ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	seats = stoi(tempNumber);
	if (seats <= 0) {
		cout << "The number of seats must be above 0.\n" << endl;
		return;
	}

	cout << "Insert the departure time: (e.g 11:00) ";
	getline(cin, departureTime);
	Time time = checkTime(departureTime);
	if (time.getHours() == -1 && time.getMinutes() == -1) {
		cout << "Not in the right format.\n" << endl;
		return;
	}
	for(auto it = rideShare->getTravels().begin(); it != rideShare->getTravels().end(); it++){

		if((*it)->getTravelDriver()->getUniqueClientID() == driverID){
			if(rideShare->differenceBetweenTimes((*it)->getTravelDepartureTime(), time) <= 60){
				cout << "Not possible to have 2 travels withing 60 minutes.\n" << endl;
				return;
			}
		}
	}

	cout << "Insert the tolerance time of the travel: (minutes)(max = 60) ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	tolerance = stoi(tempNumber);
	if(tolerance > 60){
		cout << "The maximum tolerance is 60 minutes.\n" << endl;
		return;
	}
	if (tolerance <= 0) {
		cout << "The tolerance must be above 0.\n" << endl;
		return;
	}

	cout << "Insert the ID of the departure node: ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	startPlace = stoi(tempNumber);
	if (!rideShare->existsNodeID(startPlace)) {
		cout << "\nThere is no Node with the ID: " << startPlace << endl;
		return;
	}

	cout << "Insert the ID of the end of travel node: ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	endPlace = stoi(tempNumber);
	if (!rideShare->existsNodeID(endPlace)) {
		cout << "\nThere is no Node with the ID: " << startPlace << endl;
		return;
	}
	if (endPlace == startPlace) {
		cout << "\nThe source and destiny node ID can not be the same. "
				<< endl;
		return;
	}

	int simpleTime = rideShare->getSimpleTimeRoute(startPlace, endPlace);
	vector<int> path = rideShare->getGraph().getPath(startPlace, endPlace);

	Travel * newTravel = new Travel(rideShare, seats,
			rideShare->getClientByID(driverID), time, tolerance, simpleTime,
			startPlace, endPlace, path);
	rideShare->addTravel(newTravel);

	cout << "\nTravel added with success!" << endl << endl;
	sleep(1);
}

void createNewRequest() {

	int clientID, startPlace, endPlace, toleranceTime;
	string tempNumber, departureTime;

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Insert the ID of the new Client requesting: ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	clientID = stoi(tempNumber);
	if (!rideShare->existsClientID(clientID)) {
		cout << "\nThere is no Client with the ID: " << clientID << endl;
		return;
	}

	cout << "Insert the departure time of the request: (e.g 11:00) ";
	getline(cin, departureTime);
	Time time = checkTime(departureTime);
	if (time.getHours() == -1 && time.getMinutes() == -1) {
		cout << "Not in the right format.\n" << endl;
		return;
	}

	cout << "Insert the ID of the departure node: ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	startPlace = stoi(tempNumber);
	if (!rideShare->existsNodeID(startPlace)) {
		cout << "\nThere is no Node with the ID: " << startPlace << endl;
		return;
	}

	cout << "Insert the ID of the end of travel node: ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	endPlace = stoi(tempNumber);
	if (!rideShare->existsNodeID(endPlace)) {
		cout << "\nThere is no Node with the ID: " << startPlace << endl;
		return;
	}
	if (endPlace == startPlace) {
		cout << "\nThe source and destiny node ID can not be the same. "
				<< endl;
		return;
	}

	cout << "Insert the tolerance time of the travel: (minutes)(max = 60) ";
	getline(cin, tempNumber);
	if (!is_number(tempNumber)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	toleranceTime = stoi(tempNumber);
	if (toleranceTime > 60) {
		cout << "The maximum tolerance is 60 minutes.\n" << endl;
		return;
	}

	Request * newRequest = new Request(rideShare,
			rideShare->getClientByID(clientID), checkTime(departureTime),
			startPlace, endPlace,
			rideShare->getSimpleTimeRoute(startPlace, endPlace), toleranceTime);
	rideShare->addRequest(newRequest);

	cout << "\nRequest added with success!" << endl << endl;
	sleep(1);
}

void deleteSomething(int number) {

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;

	if (number == 1)
		cout << "Insert the ID of the Client to be removed: ";
	else if (number == 2)
		cout << "Insert the ID of the Travel to be removed: ";
	else
		cout << "Insert the ID of the Request to be removed: ";

	cin.clear();
	int uniqueID;
	string tempID;
	cin.ignore(10000, '\n');
	getline(cin, tempID);

	if (!is_number(tempID)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	uniqueID = stoi(tempID);

	if (number == 1) {

		if (rideShare->removeClient(uniqueID))
			cout << "\nClient removed with success: " << uniqueID << endl;
		else
			cout << "\nThere is no Client with the ID: " << uniqueID << endl;
	} else if (number == 2) {

		if (rideShare->removeTravel(uniqueID))
			cout << "\nTravel removed with success: " << uniqueID << endl;
		else
			cout << "\nThere is no Travel with the ID: " << uniqueID << endl;
	} else {

		if (rideShare->removeRequest(uniqueID))
			cout << "\nRequest removed with success: " << uniqueID << endl;
		else
			cout << "\nThere is no Request with the ID: " << uniqueID << endl;
	}

	sleep(1);
	return;
}

bool is_number(const std::string & s) {

	string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}

void openMap() {

	gv = new GraphViewer(600, 600, false);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	gv->setBackground("docs/vilareal.png");
	gv->defineEdgeCurved(false);
	gv->createWindow(767, 792);
}

Time checkTime(string time) {

	Time timeStruct = Time(-1, -1);

	istringstream infoClient(time);
	int hour, minutes;
	char garbage;

	if (time.length() != 5 || time[2] != ':')
		return timeStruct;

	infoClient >> hour;
	infoClient >> garbage;
	infoClient >> minutes;

	if (hour > 23 || hour < 0 || minutes > 59 || minutes < 0)
		return timeStruct;

	return Time(hour, minutes);
}

void manageAllTravels(){

	rideShare->clearVectors();

	for(auto itr = rideShare->getRequests().begin(); itr != rideShare->getRequests().end(); itr++){

		for(auto itt = rideShare->getTravels().begin(); itt != rideShare->getTravels().end(); itt++){

			//Driver can not drive himself
			if((*itt)->getTravelDriver()->getUniqueClientID() == (*itr)->getClient()->getUniqueClientID())
				continue;

			//Number os seats restriction
			if((*itt)->getAvailableSeats() <= (*itt)->getAllClientsGoing().size())
				continue;

			vector<int> sources, dests;
			sources.push_back((*itt)->getTravelStartPlace());
			dests.push_back((*itt)->getTravelEndPlace());

			for(auto it = (*itt)->getAllRequests().begin(); it != (*itt)->getAllRequests().end(); it++){

				sources.push_back((*it)->getRequestStartPlace());
			}
			vector<int> path1 = bestPathWithAllNodes(bestPath(sources, dests));

			sources.push_back((*itr)->getRequestStartPlace());
			dests.push_back((*itr)->getRequestEndPlace());

			vector<int> path = bestPathWithAllNodes(bestPath(sources, dests));

			//temporal restrictions
			int fullDistance = 0, waitingDistance = 0;
			for (size_t t = 0; t < path.size() - 1; t++) {

				fullDistance += rideShare->getGraph().calculateEdgeWeight(
						path.at(t), path.at(t + 1));

				if (path.at(t + 1) == (*itr)->getRequestStartPlace()) {
					waitingDistance = fullDistance;
				}
			}
			int fullTime = fullDistance / 70.0;
			int waitingTime = waitingDistance / 70.0;

			Time finishSimpleTime = rideShare->addTimes((*itt)->getTravelDepartureTime(), (*itt)->getSimpleTime());
			Time finishFullTime = rideShare->addTimes((*itt)->getTravelDepartureTime(), fullTime);

			if(rideShare->differenceBetweenTimes(finishFullTime, finishSimpleTime) > (*itt)->getToleranceTime())
				continue;

			if(waitingDistance > (*itr)->getToleranceTime())
				continue;


			(*itt)->addClient((*itr)->getClient());
			(*itt)->addRequest((*itr));
			(*itt)->setCurrentPath(path);
			cout << "Added Client nº " << (*itr)->getClient()->getUniqueClientID() << " - "
					<< (*itr)->getClient()->getName() << " to this travel.";
		}
	}
}

vector<int> bestPath(vector<int> sources, vector<int> dests) {

	//sources 		=  1 2 6 15 4
	//				   X
	//dests   		= 10 3 8  5 9
	//				   X

	//usedSources 	=  1 2
	//usedDests  	=  10
	//lastPath		=  1 2

	vector<int> lastPath = {sources.at(0)};
	vector<int> usedSources = {sources.at(0)};
	vector<int> usedDests = {dests.at(0)};

	int minDistance = INT_MAX, minT;
	bool minDestUsed, minSourceUsed;
	bool destUsed, sourceUsed;

	for (size_t j = 0; j < (sources.size() - 1) * 2; j++) {

		for (size_t t = 1; t < dests.size(); t++) {

			//dijkstra organizing the graph through the last element of the path
			rideShare->getGraph().dijkstraShortestPath(lastPath.at(lastPath.size() - 1));

			//check if this element has been used in sources
			sourceUsed = false;
			destUsed = false;
			for (size_t k = 0; k < usedSources.size(); k++) {

				if (usedSources.at(k) == sources.at(t))
					sourceUsed = true;
			}
			//check if this element has been used in dests
			if (sourceUsed) {
				for (size_t k = 0; k < usedDests.size(); k++) {

					if (usedDests.at(k) == dests.at(t)) {

						destUsed = true;
						continue;
					}
				}
			}
			//both have been used
			if (destUsed)
				continue;
			//until this point we are just deciding which element to use next

			vector<int> path;
			if ((sourceUsed == false) && (destUsed == false)) {	//using sources

				path = rideShare->getGraph().getPath(lastPath.size() - 1, sources.at(t));
			} else if ((sourceUsed == true) && (destUsed == false)) {//using dests

				path = rideShare->getGraph().getPath(lastPath.size() - 1, dests.at(t));
			}

			int tempDist = 0;
			for (size_t k = 0; k < path.size() - 1; k++) {

				tempDist += rideShare->getGraph().calculateEdgeWeight(
						path.at(k), path.at(k + 1));
			}
			if (tempDist < minDistance) {

				minDistance = tempDist;
				minT = t;
				minSourceUsed = sourceUsed;
				minDestUsed = destUsed;
			}
		}


		if ((minSourceUsed == false) && (minDestUsed == false)) {

			usedDests.push_back(sources.at(minT));
			lastPath.push_back(sources.at(minT));
		} else if ((minSourceUsed == true) && (minDestUsed == false)) {

			usedDests.push_back(dests.at(minT));
			lastPath.push_back(dests.at(minT));
		}

		minDistance = INT_MAX;
	}

	lastPath.push_back(dests.at(0));
	return lastPath;
}

vector<int> bestPathWithAllNodes(vector<int> path) {

	vector<int> fullPath;
	for (size_t t = 0; t < path.size() - 1; t++) {

		rideShare->getGraph().dijkstraShortestPath(path.at(t));
		vector<int> tempPath = rideShare->getGraph().getPath(path.at(t), path.at(t + 1));

		for (size_t i = 0; i < tempPath.size() - 1; i++) {

			fullPath.push_back(tempPath.at(i));
		}
	}

	fullPath.push_back(path.size() - 1);

	return fullPath;
}



/*
 void RideShare::manageTravels() {

	clearVectors();

	for (auto itr = this->allRequests.begin(); itr != this->allRequests.end();
			itr++) {

		for (auto itt = this->allTravels.begin(); itt != this->allTravels.end();
				itt++) {

			if((*itt)->getTravelDriver()->getUniqueClientID() == (*itr)->getClient()->getUniqueClientID())
				continue;

			if((*itt)->getAvailableSeats()
					<= (*itt)->getAllClientsGoing().size())	//no more available seats
				continue;

			this->graph.dijkstraShortestPath((*itt)->getTravelStartPlace());
			vector<int> path1 = this->graph.getPath(
					(*itt)->getTravelStartPlace(),
					(*itr)->getRequestStartPlace());
			int totalWaitingTime = 0;
			for (size_t t = 0; t < path1.size() - 1; t++) {

				totalWaitingTime += this->graph.calculateEdgeWeight(path1.at(t), path1.at(t + 1));
			}
			totalWaitingTime /= 70.0;
			cout << "Waiting Time: " << totalWaitingTime;

			this->graph.dijkstraShortestPath((*itr)->getRequestStartPlace());
			vector<int> path2 = this->graph.getPath(
					(*itr)->getRequestStartPlace(),
					(*itr)->getRequestEndPlace());

			this->graph.dijkstraShortestPath((*itr)->getRequestEndPlace());
			vector<int> path3 = this->graph.getPath(
					(*itr)->getRequestEndPlace(), (*itt)->getTravelEndPlace());


			vector<int> fullPath;
			for (size_t t = 0; t < path1.size(); t++) {
				fullPath.push_back(path1.at(t));
			}
			for (size_t t = 1; t < path2.size(); t++) {
				fullPath.push_back(path2.at(t));
			}
			for (size_t t = 1; t < path3.size(); t++) {
				fullPath.push_back(path3.at(t));
			}

			int totalTravelMinutes = 0;
			for (size_t t = 0; t < fullPath.size() - 1; t++) {

				totalTravelMinutes += this->graph.calculateEdgeWeight(
						fullPath.at(t), fullPath.at(t + 1));
			}
			totalTravelMinutes /= 70.0;				//tempo da viagem total (min)
			cout << "\ntotalTravelMinutes: " << totalTravelMinutes;


			Time finishSimpleTime = addTimes((*itt)->getTravelDepartureTime(), (*itt)->getSimpleTime());
			cout << "\nHora que acabaria: " << finishSimpleTime.getHours() << ":" << finishSimpleTime.getMinutes();


			Time finishFullTime;
			//travel quer sair antes do request (traveler espera pelo requester = tolerancia do traveler)
			if (((*itt)->getTravelDepartureTime().getHours() == (*itr)->getRequestDepartureTime().getHours()
					&& (*itt)->getTravelDepartureTime().getMinutes() < (*itr)->getRequestDepartureTime().getMinutes())
					|| (*itt)->getTravelDepartureTime().getHours() < (*itr)->getRequestDepartureTime().getHours()) {

				cout << "\nA";
				finishFullTime = addTimes((*itr)->getRequestDepartureTime(), totalTravelMinutes);
				cout << " Hora que acaba: " << finishFullTime.getHours() << ":" << finishFullTime.getMinutes();
			}
			//mesma hora OU travel depois do request (requester espera pelo traveler = tolerancia do requester)
			else {

				cout << "\nB";
				finishFullTime = addTimes((*itt)->getTravelDepartureTime(), totalTravelMinutes);
				cout << " Hora que acaba: " << finishFullTime.getHours() << ":" << finishFullTime.getMinutes();
			}

			cout << "\ndifference: " << differenceBetweenTimes(finishFullTime, finishSimpleTime);
			cout << "\ntolerance: " << (*itt)->getToleranceTime();

			if (differenceBetweenTimes(finishFullTime, finishSimpleTime) > (*itt)->getToleranceTime())
				continue;

			cout << "\ntolerance2: " << (*itr)->getToleranceTime();
			if (totalWaitingTime > (*itr)->getToleranceTime())
				continue;

			(*itt)->addClient((*itr)->getClient());
			(*itt)->addRequest(*itr);
			(*itt)->setCurrentPath(fullPath);
			cout << "Added Client nº "
					<< (*itr)->getClient()->getUniqueClientID() << " - "
					<< (*itr)->getClient()->getName() << " to this travel.";
		}
	}
}*/
