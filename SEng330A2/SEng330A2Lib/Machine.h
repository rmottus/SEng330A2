#pragma once

#include "stdafx.h"
#include <string>
#include "MachineList.pb.h"

class MachineFactory;

/** 
* Abstract class for describing machines.
*
* The base class for representing machines from the gym.
* Includes the protocol buffer that allows the machine to be saved.
* A unique ID for based off of set of machines seen since the start of the program is maintained and automatically assigned to new machines.
* For implementations see CardioMachine and WeightMachine.
*/
class Machine {
	friend MachineFactory;
public:
	/**
	* Constructor that accepts the name to be given to the machine.
	*
	* @param n - the name for the machine.
	*/
	Machine(const std::string &n);
	/**
	* Copy constructor.
	*
	* @param m - the machine to copy.
	*/
	Machine(const Machine &m);
	/**
	* Constructor that builds a machine out of a previously created protocol buffer machine.
	*
	* @param m - the proto::Machine to create the machine from.
	*/
	Machine(const proto::Machine &m);
	/** Deconstructor. */
	~Machine() {};

	/**
	* Returns the unique ID of the machine.
	*
	* @return the ID of the machine.
	*/
	int getId() const;
	/** 
	* Returns the name of the machine. 
	*
	* @return the name of the machine.
	*/
	std::string getName() const;
	/** 
	* Returns the protocol buffer object holding the savable machine information.
	*
	* @return the proto::Machine for the machine.
	*/
	proto::Machine getProtoMachine() const;

	/** Virtual function that starts a workout on a machine. */
	virtual void beginWorkout() = 0;
	/** Virtual function that ends a workout on a machine. */
	virtual void endWorkout() = 0;
	/** 
	* Virtual function for cloning a machine.
	*
	* @return a clone of the machine
	*/
	virtual Machine* clone() = 0;
	/** 
	* Virtual function that returns the string representing the type of the machine.
	*
	* @return the type of the machine as a string.
	*/
	virtual std::string getTypeString() const = 0; 
protected:
	/**
	* The protocol buffer object that contains the savable information for the machine.
	* Savable information: Name, ID, Type.
	*/
	proto::Machine _protoMachine;
private:
	/** Static reference to the next possible unique ID for machines.*/
	static int _nextId;
};