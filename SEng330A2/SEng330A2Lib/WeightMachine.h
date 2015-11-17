#pragma once

#include "Machine.h"
#include <time.h>

class MachineFactory;

/**
* A subclass of Machine that represents a weight machine (Bench Press, Preacher Curl, Leg Press).
*
* This class represents a  Weight Machine (Bench Press, Preacher Curl, Leg Press) for the gym.
* It tracks the time that someone started working out on the machine, the weight on the machine, and the number of reps completed.
*/
class WeightMachine : public Machine {
	friend MachineFactory;
public:
	/**
	* Constructor that accepts a name and type of weight machine.
	*
	* @param n - the name for the machine.
	* @param t - the type for the machine.
	*/
	WeightMachine(const std::string &n, const proto::Machine_WeightType &t);
	/**
	* Copy constructor.
	*
	* @param w - the WeightMachine to copy.
	*/
	WeightMachine(const WeightMachine &w);
	/**
	* Constructor that accpets a protocol buffer machine to use with this machine.
	*
	* @param m - the proto::Machine to create the machine with.
	*/
	WeightMachine(const proto::Machine &m);
	/** Destructor. */
	~WeightMachine() {};

	// Inherited from Machine
	/**
	* Starts a workout on the weight machine.
	* Set the startTime to the current time and resets the repetition count.
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
	proto::Machine_WeightType getType() const;
	/** 
	* Sets the current weight of the machine to the passed value.
	*
	* @param new_weight - the new weight for the machine.
	*/
	void setWeight(const int &new_weight);
	/**
	* Returns the weight currently on the machine.
	*
	* @return the weight on the machine.
	*/
	int getWeight() const;
	/** 
	* Increments the repetition counter during a workout.
	*/
	void doRep();
	/** 
	* Returns the number of repetitions that have been completed in this workout.
	*
	* @return the number of repetitions compelted.
	*/
	int getReps() const;
	/**
	* Returns the start time of the current workout.
	*
	* @return the start time of the current workout.
	*/
	time_t getStartTime() const;

	// Static methods
	/**
	* Parses a string to determine if it represents a weight machine type.
	* Will return the corresponding type or an invalid type of none matches.
	*
	* @param t - the string to parse for the type.
	* @return the corresponding type of weight machine from the string.
	*/
	static proto::Machine_WeightType parseTypeFromString(const std::string &t);
private:
	/** The start time of the current workout. */
	time_t _startTime;
	/** The current weight on the machine (0-500). */
	int _weight;
	/** The number of repetitions compelted in the current workout. */
	int _repetitions;
};