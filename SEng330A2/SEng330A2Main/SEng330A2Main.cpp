/*! \mainpage Riley Mottus' SEng 330 Assignment 2 Documentation
*
* This solution consists of three projects:
*	- SEng330A2Lib creates a library of the base functionality for the solution.
*	- SEng330A2Main creates an executable console application that takes user input to create/save/load/print machines.
*	- SEng330A2Test creates an executable test application that tests SEng330A2Lib.
*
* Documentation for the library can mainly be found under *Classes*. For documentation on the tests see SEng330A2Test.cpp; for the console application see SEng330A2Main.cpp.
* For instructions on how to build the project, see README.md.
* 
* Uses Google Protocol Buffers 2.6.1 for saving/loading, Google Test 1.7.0 for tests, and Doxygen 1.8.10 to generate documentation.
*
* Created by Riley Mottus (V00749270) for SEng 330 at the University of Victoria in Fall 2015.
*/

/** 
* @file SEng330A2Main.cpp
* Defines the entry point for the console application.
* Reads user input to allow them to create/save/load/print a list of machines of different types.
* Uses Google Protocol Buffers to save/load. Currently, it will overwrite its current list if told to load from a file.
* Saving overwrites the file compeltely.
*/

#include "stdafx.h"
#include "CardioMachine.h"
#include "WeightMachine.h"
#include "MachineFactory.h"
#include "MachineList.pb.h"
#include <stdio.h>
#include <fstream>
#include <tchar.h>

using namespace std;
/** The list of machines currently being manipulated. */
vector<Machine*> machineList;
/** The machine factory to use to create machines. */
MachineFactory mFactory;

/**
* Adds a machine to the current list.
* Reads in the desired name and type of a new machine from the user and creates a machine of the appropriate type out of it.
* If the type is not recognised, then the user has a chance to enter a new type.
*/
void addMachine() {
	cout << "Adding Machine" << endl;

	// Get the name
	string name;
	cout << "Enter the name of the new machine: " << endl;
	getline(cin, name);

	// Keep trying to get types untill we get one that we recongnize.
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

/**
* Prints out the name, ID, and type of each stored machine to the console.
*/
void printMachines() {
	cout << "Printing Machines" << endl;

	for (Machine* m : machineList) {
		cout << "Id: " << m->getId() << endl;
		cout << "Name: " << m->getName() << endl;
		cout << "Type: " << m->getTypeString() << endl << endl;
	}
}

/**
* Handles saving the list of machines.
* Reads in a file to save to from the user and attempts to write the machine list out to it.
* Currently, this overwrites the file completely.
*/
void saveMachines() {
	string inFileName;
	cout << "Enter the file to save the machine list to: " << endl;
	getline(cin, inFileName);

	// Transform the vector of machine pointers to a proto::MachineList that can be saved.
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

/**
* Asks the user if they would like to save, and attempts to save if they respond yes.
*/
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

/**
* Loads a list of machines from a file, replacing the current list.
* If there are currently machines in the list, then the user will first be asked if they wish to save them.
* Afterwards, the user is asked for the file to load. If the file can be loaded, then the current list of 
* machines is cleared and the new entries are added.
*/
void loadMachines() {
	// Loading loses all current machines in the list, so if there any check if the user wants to save them
	if (machineList.size() > 0) {
		cout << "Loading from a new file will remove all current machines. Would you like to save?" << endl;
		checkSave();
	}

	string inFileName;
	cout << "Enter the file to load the machine list from: " << endl;
	getline(cin, inFileName);

	// Read the existing machine list from the file.
	proto::MachineList mList;
	fstream input(inFileName, ios::in | ios::binary);
	if (!mList.ParseFromIstream(&input)) {
		cerr << "Failed to parse the machine list in the file " << inFileName << "." << endl;
		cerr << "No machines have been added to the list" << endl;
		return;
	}

	// Empty the list and add full machine objects in the list
	machineList.clear();
	for (int i = 0; i < mList.machines_size(); i++) {
		const proto::Machine machine = mList.machines(i);
		machineList.push_back(mFactory.createMachine(machine));
	}
	cout << "Successfully loaded the machines from the file " << inFileName << "." << endl << endl;
}

/**
* Main entry point of the console application.
* Handles getting the next command from the user and calling the correct function. 
* When first started, it lists the possible commands for the user.
*/
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
			// Check if the machines need to be saved.
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

