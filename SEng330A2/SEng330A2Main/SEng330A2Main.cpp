// SEng330A2Main.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "CardioMachine.h"
#include "WeightMachine.h"
#include "MachineFactory.h"
#include "MachineList.pb.h"
#include <tchar.h>
#include <fstream>

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
		proto::Machine_CardioType cType = CardioMachine::parseTypeFromString(type);
		if (cType) {
			machineList.push_back(mFactory.createCardioMachine(name, cType));
			break;
		}

		proto::Machine_WeightType wType = WeightMachine::parseTypeFromString(type);
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

void saveMachines() {
	string inFileName;
	cout << "Enter the file to save the machine list to: " << endl;
	getline(cin, inFileName);

	proto::MachineList mList;
	for (Machine* m : machineList) {
		proto::Machine* protoM = mList.add_machines();
		protoM->MergeFrom(m->getProtoMachine());
	}

	// Write the new address book back to disk.
	fstream output(inFileName, ios::out | ios::trunc | ios::binary);
	if (!mList.SerializeToOstream(&output)) {
		cerr << "Failed to write machine list to file " << inFileName << "." << endl;
		return;
	}
	cout << "Successfully saved the machines to the file " << inFileName << "." << endl << endl;
}

void checkSave() {
	cout << "(Yes/no): " << endl;

	string save;
	while (true) {
		getline(cin, save);
		if (save == "Yes" || save == "yes") {
			saveMachines();
			break;
		}
		else if (save == "No" || save == "no") {
			break;
		}

		cout << "Unreconized response. Please enter Yes to save or No to continue to loading." << endl;
	}
}

void loadMachines() {
	// Loading loses all current machines in the list, so if there any check if the user wants to save them
	if (machineList.size() > 0) {
		cout << "Loading from a new file will remove all current machines. Would you like to save?" << endl;
		checkSave();
	}

	string inFileName;
	cout << "Enter the file to load the machine list from: " << endl;
	getline(cin, inFileName);

	proto::MachineList mList;
	// Read the existing machine list.
	fstream input(inFileName, ios::in | ios::binary);
	if (!mList.ParseFromIstream(&input)) {
		cerr << "Failed to parse the machine list in the file " << inFileName << "." << endl;
		cerr << "No machines have been added to the list" << endl;
		return;
	}

	// Create full objects in the list
	machineList.clear();
	for (int i = 0; i < mList.machines_size(); i++) {
		const proto::Machine machine = mList.machines(i);
		machineList.push_back(mFactory.createMachine(machine));
	}
	cout << "Successfully loaded the machines from the file " << inFileName << "." << endl << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	cout << "Welcome to the Fit Kit Exercise Tracking Software" << endl;
	cout << "To add a new machine, enter \"Add\"." << endl;
	cout << "To print the current machines, enter \"Print\"." << endl;
	cout << "To save the current machines, enter \"Save\"." << endl;
	cout << "To load the  current machines, enter \"Load\"." << endl;
	cout << "To exit the program, enter \"Exit\"." << endl;

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
		else if (command == "Save" || command == "save") {
			saveMachines();
		}
		else if (command == "Load" || command == "load") {
			loadMachines();
		}
		else if (command == "Exit" || command == "exit") {
			if (machineList.size() > 0) {
				cout << "Save before exiting?" << endl;
				checkSave();
			}
			cout << "Exitting now." << endl;
			break;
		}
		else {
			cout << "Unreconized command: " << command << ". Valid commands are: Add, Print, Save, Load, Exit." << endl;
		}
	}

	// Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();
	
	return 0;
}

