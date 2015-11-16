#pragma once

#include "Machine.h"
#include <time.h>

class MachineFactory;

class WeightMachine : public Machine {
	friend MachineFactory;
public:
	enum WeightMachineType {
		BenchPress = 1, PreacherCurl, LegPress
	};

	WeightMachine(const std::string &n, const WeightMachineType &t);
	WeightMachine(const WeightMachine &w);
	~WeightMachine();

	WeightMachineType const getType();
	void beginWorkout();
	void endWorkout();
	Machine* clone();
	std::string getTypeString();

	WeightMachineType getType() const;
	void setWeight(const int &new_weight);

	static WeightMachineType parseTypeFromString(const std::string &t);
private:
	WeightMachineType _type;
	int _weight;
	time_t _startTime;
};