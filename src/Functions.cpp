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

		double weight = 0;

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

			rideShare->addEdge(nodeID2, nodeID1, weight, 0);
			gv->addEdge(roadID, nodeID1, nodeID2, 0);
		} else {

			rideShare->addEdge(nodeID1, nodeID2, weight, 1);
			gv->addEdge(roadID, nodeID1, nodeID2, 1);
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
	gv->defineEdgeCurved(true);
	gv->createWindow(767, 792);
}
