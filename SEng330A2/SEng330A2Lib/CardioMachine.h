#pragma once

#include "Machine.h"
#include <time.h>

class MachineFactory;

/** 
* A subclass of Machine that represents a cardio machine (Treadmill, Elliptical, Stationary Bike).
*
* This class represents a  Cardio Machine (Treadmill, Elliptical, Stationary Bike) for the gym.
* It tracks the time that someone started working out on the machine and the resitance level of the machine.
*/
class CardioMachine : public Machine {
	friend MachineFactory;
public:
	/**
	* Constructor that takes the name and type of the cardio machine to create.
	*
	* @param n - the name for the new machine.
	* @param t - the type of the new machine.
	*/
	CardioMachine(const std::string &n, const proto::Machine_CardioType &t);
	/**
	* Copy constructor.
	*
	* @param c - the CardioMachine to copy.
	*/
	CardioMachine(const CardioMachine &c);
	/**
	* Constructor that accpets a protocol buffer machine to use with this machine.
	*
	* @param m - the proto::Machine to create the machine with.
	*/
	CardioMachine(const proto::Machine &m);
	/** CardioMachine deconstructor. Nothing to do. */
	~CardioMachine() {};

	// Inherited from Machine
	/**
	* Starts a workout on the cardio machine.
	* Sets the startTime to the current time.
	*/
	void beginWorkout();
	/** 
	* End a workout on the cardio machine.
	* In the future this will be expanded to create and save usage statistics.
	*/
	void endWorkout();
	/** Creates a clone of the machine. */
	Machine* clone();
	/** 
	* Returns the string representation of the machine's type.
	*
	* @return the string representation of the type of the machine.
	*/
	std::string getTypeString() const;

	// Class specific
	/**
	* Returns the type of this machine.
	*
	* @return the type of the machine.
	*/
	proto::Machine_CardioType getType() const;
	/** Increases the resistance of the machine. */
	void increaseResistance();
	/** Decreases the resistance of the machine. */
	void decreaseResistance();
	/** 
	* Returns resistance of the machine.
	*
	* @return the resistance of the machine.
	*/
	int getResistance() const;
	/**
	* Returns start time of the current workout on the machine.
	* This will be -1 if there is no active workout.
	*
	* @return the start time of the current workout.
	*/
	time_t getStartTime() const;

	// Static
	/**
	* Parses a string to determine if it represents a cardio machine type.
	* Will return the corresponding type or an invalid type of none matches.
	*
	* @param t - the string to parse for the type
	* @return the corresponding type of cardio machine from the string
	*/
	static proto::Machine_CardioType parseTypeFromString(const std::string &t);
private:
	/** The start time of the current workout. -1 if no workout is in progress. */
	time_t _startTime;
	/** The current resistance of the machine (0-5). */
	int _resistance;
};