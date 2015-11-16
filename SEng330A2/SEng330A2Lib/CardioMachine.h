#pragma once

#include "Machine.h"
#include <time.h>

class MachineFactory;

class CardioMachine : public Machine {
	friend MachineFactory;
public:
	enum CardioMachineType {
		Treadmill = 1, Elliptical, StationaryBike
	};

	CardioMachine(const std::string &n, const CardioMachineType &t);
	CardioMachine(const CardioMachine &c);
	~CardioMachine();

	// Inherited from Machine
	void beginWorkout();
	void endWorkout();
	Machine* clone();
	std::string getTypeString();

	// Class specific
	CardioMachineType getType() const;
	void increaseResistance();
	void decreaseResistance();

	// Static
	static CardioMachineType parseTypeFromString(const std::string &t);
private:
	CardioMachineType _type;
	time_t _startTime;
	int _resistance;
};