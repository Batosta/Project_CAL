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
	readTravelsFile();
	readRequestsFile();
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
		string nodeName;

		infoNode >> nodeID;
		infoNode >> garbage;

		infoNode >> xCoordinate;
		infoNode >> garbage;

		infoNode >> yCoordinate;
		infoNode >> garbage;

		getline(infoNode, nodeName, ';');

		gv->addNode(nodeID, xCoordinate, yCoordinate);
		gv->setVertexLabel(nodeID, nodeName);
		rideShare->addNode(nodeID, xCoordinate, yCoordinate, nodeName); //colocar todos os Vertex no vertexSet do Graph
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

		//gv->setEdgeLabel(roadID, roadName);
	}
	file.close();
}
void readRequestsFile() {

	ifstream file;
	string line;
	file.open("docs/requests.txt");
	while (getline(file, line)) {

		/*	ClientID/ti/me/startID/endID/tolerance/			*/

		istringstream infoRequest(line);

		int clientID, hour, minute, startID, endID, tolerance;
		char garbage;

		infoRequest >> clientID;
		infoRequest >> garbage;

		infoRequest >> hour;
		infoRequest >> garbage;

		infoRequest >> minute;
		infoRequest >> garbage;

		infoRequest >> startID;
		infoRequest >> garbage;

		infoRequest >> endID;
		infoRequest >> garbage;

		infoRequest >> tolerance;
		infoRequest >> garbage;

		Time time;
		time.setHours(hour);
		time.setMinutes(minute);
		Request * newRequest = new Request(rideShare,
				rideShare->getClientByID(clientID), time, startID, endID,
				rideShare->getSimpleTimeRoute(startID, endID), tolerance);
			rideShare->addRequest(newRequest);
	}
	file.close();
}
void readTravelsFile() {

	ifstream file;
	string line;
	file.open("docs/travels.txt");
	while (getline(file, line)) {

		/* 		DriverId/seats/ti/me/startID/endID/tolerance		*/

		istringstream infoTravel(line);

		int clientID, seats, hour, minute, startID, endID, tolerance;
		char garbage;

		infoTravel >> clientID;
		infoTravel >> garbage;

		infoTravel >> seats;
		infoTravel >> garbage;

		infoTravel >> hour;
		infoTravel >> garbage;

		infoTravel >> minute;
		infoTravel >> garbage;

		infoTravel >> startID;
		infoTravel >> garbage;

		infoTravel >> endID;
		infoTravel >> garbage;

		infoTravel >> tolerance;
		infoTravel >> garbage;

		Time time;
		time.setHours(hour);
		time.setMinutes(minute);
		rideShare->getGraph().getPath(startID, endID);
		Travel * newTravel = new Travel(rideShare, seats,
				rideShare->getClientByID(clientID), time, tolerance, rideShare->getSimpleTimeRoute(startID, endID), startID,
				endID,
				rideShare->getGraph().getPath(startID, endID));
		rideShare->addTravel(newTravel);
	}
	file.close();
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
void saveRequestsFile(){

	ofstream file("docs/request.txt");

	vector<Request *> requestsVector;

	for (Request * elem : rideShare->getRequests()) {
		requestsVector.push_back(elem);
	}

	/*	ClientID/ti/me/startID/endID/tolerance/			*/

	for (size_t i = 0; i < requestsVector.size(); i++) {
		file << requestsVector.at(i)->getClient()->getUniqueClientID() << "/";
		file << requestsVector.at(i)->getRequestDepartureTime().getHours() << "/";
		file << requestsVector.at(i)->getRequestDepartureTime().getMinutes() << "/";
		file << requestsVector.at(i)->getRequestStartPlace() << "/";
		file << requestsVector.at(i)->getRequestEndPlace() << "/";
		file << requestsVector.at(i)->getToleranceTime() << "/";

		if (i != requestsVector.size() - 1)
			file << endl;
	}
	file.close();
}
void saveTravelsFile() {

	ofstream file("docs/travels.txt");

	vector<Travel *> travelsVector;

	for (Travel * elem : rideShare->getTravels()) {
		travelsVector.push_back(elem);
	}

	/* 		DriverId/seats/ti/me/startID/endID/tolerance		*/

	for (size_t i = 0; i < travelsVector.size(); i++) {
		file << travelsVector.at(i)->getTravelDriver()->getUniqueClientID() << "/";
		file << travelsVector.at(i)->getAvailableSeats() << "/";
		file << travelsVector.at(i)->getTravelDepartureTime().getHours() << "/";
		file << travelsVector.at(i)->getTravelDepartureTime().getMinutes() << "/";
		file << travelsVector.at(i)->getTravelStartPlace() << "/";
		file << travelsVector.at(i)->getTravelEndPlace() << "/";
		file << travelsVector.at(i)->getToleranceTime() << "/";

		if (i != travelsVector.size() - 1)
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

void searchClientTravels(int id) { //searchType = 0 -> kmp						searchType = 1 -> eda

	string clientName;

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Insert the name of the client you are searching: ";
	getline(cin, clientName);
	if (clientName.size() <= 2) {
		cout << "\nPlease insert a name with at least 3 characters." << endl;
		return;
	}
	cout << endl << endl;

	if(id == 0)
		rideShare->searchClientTravelsKMP(clientName);
	else
		rideShare->searchClientTravelEDA(clientName);
}

void findFastestRoute(int id) {

	string sourceName;
	string destinyName;
	vector<string> foundPlaces;

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Insert the name of the source place: ";
	getline(cin, sourceName);

	if(sourceName.size()<=2){
		cout << "\nPlease insert a name with at least 3 characters" << endl;
		return;
	}

	foundPlaces = rideShare->existsNodeName(sourceName, id);

	int n = foundPlaces.size();
	if (n == 0) {

		cout << "\nThere is no place with the name: " << sourceName << endl;
		return;
	} else if (n == 1) {

		cout << "\nDid you mean " << foundPlaces.at(0) << "? (Y/N)";
		string answer;
		getline(cin, answer);
		if (answer != "Y" && answer != "y" )
			return;
		sourceName = foundPlaces.at(0);
	} else {

		cout << "\nWhich of the following places did you mean?\n";

		for (int i = 0; i < n; i++) {

			cout << i << " - " << foundPlaces.at(i) << endl;
		}

		cout << "Choose one of the numbers: ";
		string tempNumber;

		getline(cin, tempNumber);

		if (!is_number(tempNumber)) {
			cout << "Not an integer.\n" << endl;
			return;
		}

		int number = stoi(tempNumber);

		if (number < 0 || number > n) {
			cout << "Not in range number.\n" << endl;
			return;
		}
		sourceName = foundPlaces[number];
	}


	cout << "Insert the name of the destiny place: ";

	getline(cin, destinyName);

	if(destinyName.size()<=2){
		cout << "\nPlease insert a name with at least 3 characters" << endl;
		return;
	}

	foundPlaces = rideShare->existsNodeName(destinyName, id);

	n = foundPlaces.size();
	if (n == 0) {

		cout << "\nThere is no place with the name: " << destinyName << endl;

		return;
	} else if (n == 1) {

		cout << "\nDid you mean " << foundPlaces.at(0) << "? (Y/N)";

		string answer;
		getline(cin, answer);

		if (answer != "Y" && answer != "y")
			return;
		destinyName = foundPlaces[0];
	} else {

		cout << "\nWhich of the following places did you mean?\n";
		for (int i = 0; i < n; i++) {

			cout << i << " - " << foundPlaces[i] << endl;
		}
		cout << "Choose one of the numbers: ";
		string tempNumber;
		getline(cin, tempNumber);

		if (!is_number(tempNumber)) {
			cout << "Not an integer.\n" << endl;
			return;
		}

		int number = stoi(tempNumber);
		if (number < 0 || number > n) {
			cout << "Not in range number.\n" << endl;
			return;
		}
		destinyName = foundPlaces.at(number);
	}


	int sourceID = rideShare->getIdByName(sourceName);
	int destID = rideShare->getIdByName(destinyName);
	cout << "course name: " << (*rideShare->getGraph().getVertexSet().at(sourceID+1)).getVertexName() << endl;

	if (sourceID == destID) {
		cout << "\nThe source and destiny place can not be the same. " << endl;
		return;
	}

	cout << "test xixi \n";
	vector<int> path = rideShare->getFastestRoute(sourceID, destID);
	showRouteMap(path);
}
void findFastestRouteThroughPoints(int id) {

	string sourceName;
	string destinyName;
	vector<string> foundPlaces;
	int sourceID, destID, numberPoints, middlePointID;
	vector<int> middlePoints;

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Insert the name of the source place: ";
		getline(cin, sourceName);

		if(sourceName.size()<=2){
			cout << "\nPlease insert a name with at least 3 characters" << endl;
			return;
		}


		foundPlaces = rideShare->existsNodeName(sourceName, id);

		int n = foundPlaces.size();
		if (n == 0) {

			cout << "\nThere is no place with the name: " << sourceName << endl;
			return;
		} else if (n == 1) {

			cout << "\nDid you mean " << foundPlaces.at(0) << "? (Y/N)";
			string answer;
			getline(cin, answer);
			if (answer != "Y" && answer != "y" )
				return;
			sourceName = foundPlaces.at(0);
		} else {

			cout << "\nWhich of the following places did you mean?\n";
			for (int i = 0; i < n; i++) {

				cout << i << " - " << foundPlaces[i] << endl;
			}
			cout << "Choose one of the numbers: ";
			string tempNumber;
			getline(cin, tempNumber);

			if (!is_number(tempNumber)) {
				cout << "Not an integer.\n" << endl;
				return;
			}

			int number = stoi(tempNumber);
			if (number < 0 || number > n) {
				cout << "Not in range number.\n" << endl;
				return;
			}
			destinyName = foundPlaces.at(number);
		}

	string tempNumber;

	sourceID = rideShare->getIdByName(sourceName);
	middlePoints.push_back(sourceID-1);

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

		cout << "Insert the next place: ";
		getline(cin, sourceName);
		if(sourceName.size()<=2){
			cout << "\nPlease insert a name with at least 3 characters" << endl;
			return;
		}


		foundPlaces = rideShare->existsNodeName(sourceName, id);

		int n = foundPlaces.size();
		if (n == 0) {

			cout << "\nThere is no place with the name: " << sourceName << endl;
			return;
		} else if (n == 1) {

			cout << "\nDid you mean " << foundPlaces.at(0) << "? (Y/N)";
			string answer;
			getline(cin, answer);
			if (answer != "Y" && answer != "y" )
				return;
			sourceName = foundPlaces.at(0);
		} else {

			cout << "\nWhich of the following places did you mean?\n";
			for (int i = 0; i < n; i++) {

				cout << i << " - " << foundPlaces.at(i) << endl;
			}
			cout << "Choose one of the numbers: ";
			string tempNumber;
			getline(cin, tempNumber);

			if (!is_number(tempNumber)) {
				cout << "Not an integer.\n" << endl;
				return;
			}

			int number = stoi(tempNumber);
			if (number < 0 || number > n) {
				cout << "Not in range number.\n" << endl;
				return;
			}
			destinyName = foundPlaces.at(number);
		}
		sourceID = rideShare->getIdByName(sourceName);
		middlePoints.push_back(middlePointID-1);
	}

	cout << "Insert the ID of the destiny node: ";
	getline(cin, sourceName);
	if(sourceName.size()<=2){
		cout << "\nPlease insert a name with at least 3 characters" << endl;
		return;
	}

	foundPlaces = rideShare->existsNodeName(sourceName, id);

	n = foundPlaces.size();
	if (n == 0) {

		cout << "\nThere is no place with the name: " << sourceName << endl;
		return;
	} else if (n == 1) {

		cout << "\nDid you mean " << foundPlaces.at(0) << "? (Y/N)";
		string answer;
		getline(cin, answer);
		if (answer != "Y" && answer != "y" )
			return;
		sourceName = foundPlaces.at(0);
	} else {

		cout << "\nWhich of the following places did you mean?\n";
		for (int i = 0; i < n; i++) {

			cout << i << " - " << foundPlaces[i] << endl;
		}
		cout << "Choose one of the numbers: ";
		string tempNumber;
		getline(cin, tempNumber);

		if (!is_number(tempNumber)) {
			cout << "Not an integer.\n" << endl;
			return;
		}

		int number = stoi(tempNumber);
		if (number < 0 || number > n) {
			cout << "Not in range number.\n" << endl;
			return;
		}
		destinyName = foundPlaces.at(number);
	}

//	if (destID == sourceID) {
//		cout << "\nThe source and destiny ID can not be the same. " << endl;
//		return;
//	}

	sourceID = rideShare->getIdByName(sourceName);
	middlePoints.push_back(destID-1);

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
void createNewTravel(int id) {

	int driverID, seats, tolerance;
	string tempNumber;
	string sourceName;
	string destinyName;
	string departureTime;
	vector<string> foundPlaces;

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
//	for(auto it = rideShare->getTravels().begin(); it != rideShare->getTravels().end(); it++){
//
//		if((*it)->getTravelDriver()->getUniqueClientID() == driverID){
//			if(rideShare->differenceBetweenTimes((*it)->getTravelDepartureTime(), time) <= 60){
//				cout << "Not possible to have 2 travels withing 60 minutes.\n" << endl;
//				return;
//			}
//		}
//	}

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

	cout << "Insert the name of the departure place: ";
	getline(cin, sourceName);
	if(sourceName.size()<=2){
		cout << "\nPlease insert a name with at least 3 characters" << endl;
		return;
	}

	foundPlaces = rideShare->existsNodeName(sourceName, id);

	int n = foundPlaces.size();
	if (n == 0) {

		cout << "\nThere is no place with the name: " << sourceName << endl;
		return;
	} else if (n == 1) {

		cout << "\nDid you mean " << foundPlaces.at(0) << "? (Y/N)";
		string answer;
		getline(cin, answer);
		if (answer != "Y" && answer != "y" )
			return;
		sourceName = foundPlaces.at(0);
	} else {

		cout << "\nWhich of the following places did you mean?\n";

		for (int i = 0; i < n; i++) {

			cout << i << " - " << foundPlaces.at(i) << endl;
		}

		cout << "Choose one of the numbers: ";
		string tempNumber;

		getline(cin, tempNumber);

		if (!is_number(tempNumber)) {
			cout << "Not an integer.\n" << endl;
			return;
		}

		int number = stoi(tempNumber);

		if (number < 0 || number > n) {
			cout << "Not in range number.\n" << endl;
			return;
		}
		sourceName = foundPlaces[number];
	}

	cout << "Insert the name of the travel place: ";
	getline(cin, destinyName);
	if(destinyName.size()<=2){
		cout << "\nPlease insert a name with at least 3 characters" << endl;
		return;
	}

	foundPlaces = rideShare->existsNodeName(destinyName, id);

	n = foundPlaces.size();
	if (n == 0) {

		cout << "\nThere is no place with the name: " << destinyName << endl;
		return;
	} else if (n == 1) {

		cout << "\nDid you mean " << foundPlaces.at(0) << "? (Y/N)";
		string answer;
		getline(cin, answer);
		if (answer != "Y" && answer != "y" )
			return;
		destinyName = foundPlaces.at(0);
	} else {

		cout << "\nWhich of the following places did you mean?\n";

		for (int i = 0; i < n; i++) {

			cout << i << " - " << foundPlaces.at(i) << endl;
		}

		cout << "Choose one of the numbers: ";
		string tempNumber;

		getline(cin, tempNumber);

		if (!is_number(tempNumber)) {
			cout << "Not an integer.\n" << endl;
			return;
		}

		int number = stoi(tempNumber);

		if (number < 0 || number > n) {
			cout << "Not in range number.\n" << endl;
			return;
		}
		destinyName = foundPlaces[number];
	}

	int sourceID = rideShare->getIdByName(sourceName);
	int destID = rideShare->getIdByName(destinyName);
	cout << "id : " << sourceID << endl;
	cout << "id dest : " << destID << endl;
	cout << "course name: " << sourceName << endl;

	cout << "course name: " << (*rideShare->getGraph().getVertexSet().at(sourceID+1)).getVertexName() << endl;

	cout << "dest name: " << destinyName << endl;

	if (sourceID == destID) {
		cout << "\nThe source and destiny place can not be the same. " << endl;
		return;
	}

	int simpleTime = rideShare->getSimpleTimeRoute(sourceID, destID);
	vector<int> path = rideShare->getGraph().getPath(sourceID, destID);

	Travel * newTravel = new Travel(rideShare, seats,
			rideShare->getClientByID(driverID), time, tolerance, simpleTime,
			sourceID, destID, path);
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

	vector<Request *> requests = rideShare->getRequests();
	vector<Travel * > travels = rideShare->getTravels();

	for(auto itr = requests.begin(); itr != requests.end(); itr++){

		for(auto itt = travels.begin(); itt != travels.end(); itt++){

			//check if request is in ANY travel
			if((*itr)->getAdded()==true)
				continue;

			//check if client is already in this travel  			necessary??
			for(unsigned int i = 0 ; i < (*itt)->getAllClientsGoing().size() ; i++){
				if((*itr)->getClient()->getUniqueClientID() == (*itt)->getAllClientsGoing().at(i)->getUniqueClientID())
					continue;
			}

			//Driver can not drive himself
			if((*itt)->getTravelDriver()->getUniqueClientID() == (*itr)->getClient()->getUniqueClientID()) {
				continue;
			}
			//Number os seats restriction
			if((*itt)->getAvailableSeats() <= (*itt)->getAllClientsGoing().size()){
				continue;
			}
			vector<int> sources, dests;
			sources.push_back((*itt)->getTravelStartPlace());
			dests.push_back((*itt)->getTravelEndPlace());

			for(size_t g = 0; g < (*itt)->getAllSources().size(); g++){

				sources.push_back((*itt)->getAllSources().at(g));
			}
			for(size_t g = 0; g < (*itt)->getAllDests().size(); g++){

				dests.push_back((*itt)->getAllDests().at(g));
			}
			sources.push_back((*itr)->getRequestStartPlace());
			dests.push_back((*itr)->getRequestEndPlace());
			vector<int> path = bestPathWithAllNodes(bestPath(sources, dests));

			//temporal restrictions
			int fullDistance = 0;
			for (size_t t = 0; t < path.size() - 1; t++) {

				fullDistance += rideShare->getGraph().calculateEdgeWeight(
						path.at(t), path.at(t + 1));

			}
			int fullTime = fullDistance / 70.0;

			Time finishSimpleTime = rideShare->addTimes((*itt)->getTravelDepartureTime(), (*itt)->getSimpleTime());
			Time finishFullTime = rideShare->addTimes((*itt)->getTravelDepartureTime(), fullTime);

			finishFullTime = rideShare->addTimes(finishFullTime, rideShare->differenceBetweenTimes((*itt)->getTravelDepartureTime(), (*itr)->getRequestDepartureTime()));

			if(rideShare->differenceBetweenTimes(finishFullTime, finishSimpleTime) > (*itt)->getToleranceTime()){
				continue;
			}


			(*itt)->addClient((*itr)->getClient());
			(*itt)->addSource((*itr)->getRequestStartPlace());
			(*itt)->addDest((*itr)->getRequestEndPlace());
			(*itt)->setCurrentPath(path);
			(*itt)->addRequest(*itr);

		}
	}

	cout << "\nAll travels are now updated." << endl << endl;
	sleep(1);
}

vector<int> bestPath(vector<int> sources, vector<int> dests) {

	vector<int> lastPath = {sources.at(0)};
	vector<int> usedSources = {sources.at(0)};
	vector<int> usedDests = {dests.at(0)};

	int minDistance = INT_MAX, minT;
	bool minDestUsed, minSourceUsed;
	bool destUsed, sourceUsed;

	for (size_t j = 0; j < (sources.size() - 1) * 2; j++) {

		vector<int> path;
		vector<int> minpath;
		for (size_t t = 1; t < dests.size(); t++) {

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


			//dijkstra organizing the graph through the last element of the path
			int size = lastPath.size();
			rideShare->getGraph().dijkstraShortestPath(lastPath.at(size - 1));

			if ((sourceUsed == false) && (destUsed == false)) {	//using sources

				int value = lastPath.size() - 1;
				path = rideShare->getGraph().getPath(lastPath.at(value), sources.at(t));
			} else if ((sourceUsed == true) && (destUsed == false)) {//using dests

				int value = lastPath.size() - 1;
				path = rideShare->getGraph().getPath(lastPath.at(value), dests.at(t));
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
				minpath=path;
			}

		}


		if ((minSourceUsed == false) && (minDestUsed == false)) {

			usedSources.push_back(sources.at(minT));
			lastPath.push_back(sources.at(minT));
		} else if ((minSourceUsed == true) && (minDestUsed == false)) {

			usedDests.push_back(dests.at(minT));
			lastPath.push_back(dests.at(minT));
		}

		minDistance = INT_MAX;
	}

	rideShare->getGraph().dijkstraShortestPath(lastPath.at(lastPath.size() - 1));
	vector<int> tempPath = rideShare->getGraph().getPath(lastPath.at(lastPath.size() - 1), dests.at(0));
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

	fullPath.push_back(path.at(path.size() - 1));

	return fullPath;
}
