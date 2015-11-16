#pragma once

#include "stdafx.h"
#include <string>
#include "MachineList.pb.h"

class MachineFactory;

class Machine {
	friend MachineFactory;
public:
	Machine(const std::string &n);
	Machine(const Machine &m);
	Machine(const proto::Machine &m);
	~Machine() {};

	const int getId() const;
	std::string getName() const;
	const proto::Machine getProtoMachine() const;

	virtual void beginWorkout() = 0;
	virtual void endWorkout() = 0;
	virtual Machine* clone() = 0;
	virtual std::string getTypeString() = 0; 
protected:
	proto::Machine _protoMachine;
private:
	static int _nextId;
};