#pragma once

#include "CardioMachine.h"
#include "WeightMachine.h"

class MachineFactoryFixture;

class MachineFactory {
	friend MachineFactoryFixture;
public:
	MachineFactory();
	~MachineFactory();

	CardioMachine* createCardioMachine(const std::string &name, const proto::Machine_CardioType &t);
	WeightMachine* createWeightMachine(const std::string &name, const proto::Machine_WeightType &t);
	Machine* createMachine(const proto::Machine &m);

private:
	CardioMachine* _cmProto;
	WeightMachine* _wmProto;
};