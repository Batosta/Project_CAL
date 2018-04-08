#include "Functions.h"
#include "Client.h"
#include "Rideshare.h"
#include "graphviewer.h"
#include "edgetype.h"

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

void createRideShare() {

	vector<Client *> clients;
	vector<Travel *> travels;
	rideShare = new RideShare(clients, travels);
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
	else
		i = 2;

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

	rideShare->showFastestRoute(sourceID, destID);
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


	for(size_t t = 0; t < middlePoints.size() - 1; t++){

		rideShare->showFastestRoute(middlePoints.at(t), middlePoints.at(t+1));
	}
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

	int driverID, seats;
	string tempID, tempSeats;
	string startTime, startPlace, endPlace;

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Insert the ID of the new Client who is driving: ";
	getline(cin, tempID);
	if (!is_number(tempID)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	driverID = stoi(tempID);
	if (!rideShare->existsClientID(driverID)) {
		cout << "\nThere is no Client with the ID: " << driverID << endl;
		return;
	}

	cout << "Insert the number of available seats: ";
	getline(cin, tempSeats);
	if (!is_number(tempSeats)) {
		cout << "Not an integer.\n" << endl;
		return;
	}
	seats = stoi(tempSeats);

	cout << "Insert the departure time: ";
	getline(cin, startTime);

	cout << "Insert the departure place: ";
	getline(cin, startPlace);

	cout << "Insert the destination: ";
	getline(cin, endPlace);

	Travel * newTravel = new Travel(rideShare, seats,
			rideShare->getClientByID(driverID), startTime, startPlace,
			endPlace);
	rideShare->addTravel(newTravel);
	cout << "\nTravel added with success!" << endl << endl;

	sleep(1);
}

void deleteClient() {

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cout << "Insert the ID of the Client to be removed: ";
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

	if (rideShare->removeClient(uniqueID))
		cout << "\nClient removed with success: " << uniqueID << endl;
	else
		cout << "\nThere is no Client with the ID: " << uniqueID << endl;

	sleep(1);
	return;
}
void deleteTravel() {

	cout << endl << endl;
	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl << endl;
	cout << "Insert the ID of the Travel to be removed: ";
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

	if (rideShare->removeTravel(uniqueID))
		cout << "\nTravel removed with success: " << uniqueID << endl;
	else
		cout << "\nThere is no Travel with the ID: " << uniqueID << endl;

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
