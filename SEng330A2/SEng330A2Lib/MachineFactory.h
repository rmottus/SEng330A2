#pragma once

#include "CardioMachine.h"
#include "WeightMachine.h"

class MachineFactory {
public:
	MachineFactory();
	~MachineFactory();

	Machine* createCardioMachine(const std::string &name, const CardioMachine::CardioMachineType &t);
	Machine* createWeightMachine(const std::string &name, const WeightMachine::WeightMachineType &t);

private:
	Machine* _cmProto;
	Machine* _wmProto;
};