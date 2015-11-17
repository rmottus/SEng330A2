#pragma once

#include "Machine.h"
#include <time.h>

class MachineFactory;

/** 
* A subclass of Machine that represents a Cardio Machine (Treadmill, Elliptical, Stationary Bike).
*
* This class represents a  Cardio Machine (Treadmill, Elliptical, Stationary Bike) for the gym.
* It tracks the time that someone started on the machine and the resitance level of the machine.
*/
class CardioMachine : public Machine {
	friend MachineFactory;
public:
	/** CardioMachine constructor that takes the name and type of the cardio machine to create. */
	CardioMachine(const std::string &n, const proto::Machine_CardioType &t);
	/** CardioMachine copy constructor. */
	CardioMachine(const CardioMachine &c);
	/** CardioMachine constructor that accpets a protocol buffer machine to use with this machine. */
	CardioMachine(const proto::Machine &m);
	/** CardioMachine deconstructor. Nothing to do. */
	~CardioMachine() {};

	// Inherited from Machine
	void beginWorkout();
	void endWorkout();
	Machine* clone();
	std::string getTypeString();

	// Class specific
	proto::Machine_CardioType getType() const;
	void increaseResistance();
	void decreaseResistance();
	int getResistance() const;
	time_t getStartTime() const;

	// Static
	static proto::Machine_CardioType parseTypeFromString(const std::string &t);
private:
	time_t _startTime;
	int _resistance;
};