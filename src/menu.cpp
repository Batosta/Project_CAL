#include "menu.h"

using namespace std;

void mainMenu() {

	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl;
	cout << " 1 - Clients Management" << endl;
	cout << " 2 - Travels Management" << endl;
	cout << " 3 - Graph Management" << endl;
	cout << " 4 - Exit" << endl;
	int opcao = 0;

	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 4) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				clientsMenu();
				break;
			case 2:
				travelsMenu();
				break;
			case 3:
				graphMenu();
				break;
			case 4:
				leave();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}
		}

		else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}
}

void clientsMenu() {

	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl;
	cout << " 1 - Create new Client" << endl;
	cout << " 2 - Remove Client" << endl;
	cout << " 3 - See All Clients" << endl;
	cout << " 4 - Return" << endl;
	cout << " 5 - Exit" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 5) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				createNewClient();
				goBack();
				break;
			case 2:
				deleteSomething(1);
				goBack();
				break;
			case 3:
				seeAllSomething("clients");
				goBack();
				break;
			case 4:
				mainMenu();
				break;
			case 5:
				leave();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}
}

void travelsMenu() {

	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl;
	cout << " 1 - Create new Travel" << endl;
	cout << " 2 - Remove Travel" << endl;
	cout << " 3 - See All Travels" << endl;
	cout << " 4 - Search for a client on Travels" << endl;
	cout << " 5 - Create a new Request" << endl;
	cout << " 6 - Remove Request" << endl;
	cout << " 7 - See All Requests" << endl;
	cout << " 8 - Manage All Travels" << endl;
	cout << " 9 - Return" << endl;
	cout << " 10 - Exit" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 10) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				stringAlgorithmTypeMenu(3);
				goBack();
				break;
			case 2:
				deleteSomething(2);
				goBack();
				break;
			case 3:
				seeAllSomething("travels");
				goBack();
				break;
			case 4:
				stringAlgorithmTypeMenu(4);
				goBack();
				break;
			case 5:
				createNewRequest();
				goBack();
				break;
			case 6:
				deleteSomething(3);
				goBack();
				break;
			case 7:
				seeAllSomething("requests");
				goBack();
				break;
			case 8:
				manageAllTravels();
				goBack();
				break;
			case 9:
				mainMenu();
				break;
			case 10:
				leave();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}
}

void graphMenu() {

	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl;
	cout << " 1 - See All Nodes" << endl;
	cout << " 2 - Find fastest route" << endl;
	cout << " 3 - Find fastest route going through some points" << endl;
	cout << " 4 - Return" << endl;
	cout << " 5 - Exit" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 5) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				seeAllSomething("nodes");
				goBack();
				break;
			case 2:
				stringAlgorithmTypeMenu(1);
				goBack();
				break;
			case 3:
				stringAlgorithmTypeMenu(2);
				goBack();
				break;
			case 4:
				mainMenu();
				break;
			case 5:
				leave();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}
}

void stringAlgorithmTypeMenu(int id) {

	cout << "-----------" << endl;
	cout << "RideSharing" << endl;
	cout << "-----------" << endl;
	cout << endl;
	cout << " 1 - String Matching" << endl;
	cout << " 2 - Approximate String Matching" << endl;
	cout << " 3 - Return" << endl;
	cout << " 4 - Exit" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 4) {
		if (cin >> opcao) {

			switch (opcao) {
			case 1:
				if(id == 1)
					findFastestRoute(0);
				else if(id == 2)
					findFastestRouteThroughPoints(0);
				else if(id == 3)
					createNewTravel(0);
				else if(id == 4)
					searchClientTravels(0);
				goBack();
				break;
			case 2:
				if(id == 1)
					findFastestRoute(1);
				else if(id == 2)
					findFastestRouteThroughPoints(1);
				else if(id == 3)
					createNewTravel(1);
				else if(id == 4)
					searchClientTravels(1);
				goBack();
				break;
			case 3:
				mainMenu();
				break;
			case 4:
				leave();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}
}

void goBack() {
	cout << endl << endl;
	cout << " 1 - Return to the Main Menu" << endl;
	cout << " 2 - Exit" << endl;

	int opcao = 0;
	cout << endl;
	cout << "Choose an option: ";
	while (opcao < 1 || opcao > 2) {
		if (cin >> opcao) {
			switch (opcao) {
			case 1:
				mainMenu();
				break;
			case 2:
				leave();
				break;
			default:
				cout << "Invalid option. Please, choose another option: ";
			}
		} else {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid option. Please, choose another option: ";
		}
	}
}

void leave() {
	string opcao;
	cout << endl;
	cout << "Do you wish to save your changes? (Y/N): ";
	cin.clear();
	cin.ignore(10000, '\n');
	while (opcao != "y" && opcao != "Y" && opcao != "n" && opcao != "N") {
		getline(cin, opcao);
		if (opcao == "y" || opcao == "Y") {
			saveClientsFile();
			saveRequestsFile();
			saveTravelsFile();
			cout << "\nSaved changes! Leaving... \n";
			sleep(1);
			break;
		}
		if (opcao == "n" || opcao == "N") {
			cout << "\nLeaving...\n";
			sleep(1);
			break;
		} else {
			cout << "Invalid option. Please, choose another option: ";
		}
	}
	exit(0);
}
