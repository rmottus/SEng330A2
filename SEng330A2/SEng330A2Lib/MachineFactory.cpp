#include "stdafx.h"
#include "MachineFactory.h"

MachineFactory::MachineFactory() : _cmProto(nullptr), _wmProto(nullptr) {}

MachineFactory::~MachineFactory() {
	delete _cmProto;
	delete _wmProto;
}

Machine* MachineFactory::createCardioMachine(const std::string &n, const CardioMachine::CardioMachineType &t) {
	Machine* result;
	if (_cmProto) {
		result = _cmProto->clone();
		result->_name = n;
		((CardioMachine*)result)->_type = t;
	}
	else {
		result = new CardioMachine(n, t);
		_cmProto = result;
	}

	return result;
}

Machine* MachineFactory::createWeightMachine(const std::string &n, const WeightMachine::WeightMachineType &t) {
	Machine* result;
	if (_wmProto) {
		result = _wmProto->clone();
		result->_name = n;
		((WeightMachine*)result)->_type = t;
	}
	else {
		result = new WeightMachine(n, t);
		_wmProto = result;
	}

	return result;
}