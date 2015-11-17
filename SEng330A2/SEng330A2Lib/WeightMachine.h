#pragma once

#include "Machine.h"
#include <time.h>

class MachineFactory;

class WeightMachine : public Machine {
	friend MachineFactory;
public:

	WeightMachine(const std::string &n, const proto::Machine_WeightType &t);
	WeightMachine(const WeightMachine &w);
	WeightMachine(const proto::Machine &m);
	~WeightMachine() {};

	proto::Machine_WeightType const getType();
	void beginWorkout();
	void endWorkout();
	Machine* clone();
	std::string getTypeString();

	proto::Machine_WeightType getType() const;
	void setWeight(const int &new_weight);
	int getWeight() const;
	void doRep();
	int getReps() const;
	time_t getStartTime() const;

	static proto::Machine_WeightType parseTypeFromString(const std::string &t);
private:
	time_t _startTime;
	int _weight;
	int _repetitions;
};