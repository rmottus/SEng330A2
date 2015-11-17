#pragma once

#include "CardioMachine.h"
#include "WeightMachine.h"

class MachineFactoryFixture;

/** 
* A factory class for creating machine objects.
*
* This factory uses the prototype pattern of machines to store a prototype of the two different type of machines.
* When creating a new machine, it will clone the prototype if it exists or create a new machine and store it for future cloning if it does not.
* This class is a friend of the Machine, CardioMachine, and WeightMachine classes.
*/
class MachineFactory {
	friend MachineFactoryFixture;
public:
	/** Base constructor. */
	MachineFactory();
	/** Base deconstructor. */
	~MachineFactory() {};

	/**
	* Creates a new CardioMachine from a name and a Machine_CardioType by cloning an internal CardioMachine.
	*
	* @param name - the name of the machine to create.
	* @param t - the proto::Machine_CardioType to give to the new machine.
	* @return a pointer a new CardioMachine with the passed properties
	*/
	CardioMachine* createCardioMachine(const std::string &name, const proto::Machine_CardioType &t);
	/**
	* Creates a new WeightMachine from a name and a Machine_WeightType by cloning an internal WeightMachine.
	*
	* @param name - the name of the machine to create.
	* @param t - the proto::Machine_WeightType to give to the new machine..
	* @return a pointer a new WeightMachine with the passed properties
	*/
	WeightMachine* createWeightMachine(const std::string &name, const proto::Machine_WeightType &t);
	/**
	* Creates a new machine from a protocol buffer machine object.
	* The type of this machine can be determined from the proto::Machine object.
	* Will clone an existing machine.
	*
	* @param m - the proto::Machine object to use when building the machine.
	* @return a pointer to a new Machine with the passed information.
	*/
	Machine* createMachine(const proto::Machine &m);

private:
	/** A pointer to a CardioMachine that will be used when cloning. */
	CardioMachine _cmProto;
	/** A pointer to a WeightMachine that will be used when cloning. */
	WeightMachine _wmProto;
};