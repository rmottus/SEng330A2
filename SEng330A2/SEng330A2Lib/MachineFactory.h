#pragma once

#include "CardioMachine.h"
#include "WeightMachine.h"

class MachineFactory {
public:
	MachineFactory();
	~MachineFactory();

	Machine* createCardioMachine(const std::string &name, const proto::Machine_CardioType &t);
	Machine* createWeightMachine(const std::string &name, const proto::Machine_WeightType &t);
	Machine* createMachine(const proto::Machine &m);

private:
	Machine* _cmProto;
	Machine* _wmProto;
};