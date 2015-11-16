#pragma once

#include "Machine.h"
#include <time.h>

class MachineFactory;

class CardioMachine : public Machine {
	friend MachineFactory;
public:
	CardioMachine(const std::string &n, const proto::Machine_CardioType &t);
	CardioMachine(const CardioMachine &c);
	CardioMachine(const proto::Machine &m);
	~CardioMachine();

	// Inherited from Machine
	void beginWorkout();
	void endWorkout();
	Machine* clone();
	std::string getTypeString();

	// Class specific
	proto::Machine_CardioType getType() const;
	void increaseResistance();
	void decreaseResistance();

	// Static
	static proto::Machine_CardioType parseTypeFromString(const std::string &t);
private:
	time_t _startTime;
	int _resistance;
};