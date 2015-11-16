#pragma once

#include "stdafx.h"
#include <string>

class MachineFactory;

class Machine {
	friend MachineFactory;
public:
	Machine(const std::string &n);
	Machine(const Machine &m);
	~Machine() {};

	const int getId() const;
	std::string getName() const;

	virtual void beginWorkout() = 0;
	virtual void endWorkout() = 0;
	virtual Machine* clone() = 0;
	virtual std::string getTypeString() = 0;
private:
	const int _id;
	static int _nextId;
	std::string _name;
};