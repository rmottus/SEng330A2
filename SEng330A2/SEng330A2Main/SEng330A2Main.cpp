// SEng330A2Main.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "CardioMachine.h"
#include "WeightMachine.h"
#include "MachineFactory.h"

using namespace std;

vector<Machine*> machineList;
MachineFactory mFactory;

void addMachine() {
	cout << "Adding Machine" << endl;

	string name;
	cout << "Enter the name of the new machine: " << endl;
	getline(cin, name);

	string type;
	while (true) {
		cout << "Enter the type of the new machine: " << endl;
		getline(cin, type);
		CardioMachine::CardioMachineType cType = CardioMachine::parseTypeFromString(type);
		if (cType) {
			machineList.push_back(mFactory.createCardioMachine(name, cType));
			break;
		}

		WeightMachine::WeightMachineType wType = WeightMachine::parseTypeFromString(type);
		if (wType) {
			machineList.push_back(mFactory.createWeightMachine(name, wType));
			break;
		}

		cout << "Did not recognise machine type: " << type << endl;
	}

	cout << "Sucessfully added the new machine." << endl << endl;
}

void printMachines() {
	cout << "Printing Machines" << endl;

	for (Machine* m : machineList) {
		cout << "Id: " << m->getId() << endl;
		cout << "Name: " << m->getName() << endl;
		cout << "Type: " << m->getTypeString() << endl << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Welcome to the Fit Kit Exercise Tracking Software" << endl;
	cout << "To add a new machine, enter \"Add\"." << endl;
	cout << "To print current machines, enter \"Print\"." << endl;
	cout << "To exit current machines, enter \"Exit\"." << endl;

	string command;

	while (true) {
		cout << "Please enter a command." << endl;
		getline(cin, command);

		if (command == "Add" || command == "add") {
			addMachine();
		}
		else if (command == "Print" || command == "print") {
			printMachines();
		}
		else if (command == "Exit" || command == "exit") {
			cout << "Exitting now." << endl;
			break;
		}
		else {
			cout << "Unreconized command: " << command << ". Valid commands are: Add, Print, Exit." << endl;
		}
	}
	
	return 0;
}

