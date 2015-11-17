#include "stdafx.h"
#include "MachineFactory.h"

/**
* Creates the objects to use when cloning.
*/
MachineFactory::MachineFactory() :
	_cmProto("Proto", proto::Machine_CardioType::Machine_CardioType_ELLIPTICAL),
	_wmProto("Proto", proto::Machine_WeightType::Machine_WeightType_BENCHPRESS) {
	Machine::_nextId -= 2;
	_cmProto._protoMachine.set_id(-1);
	_wmProto._protoMachine.set_id(-1);
}

/**
* The new machine will be given a new ID, and default values for startTime (-1), and resistance(0).
*/
CardioMachine* MachineFactory::createCardioMachine(const std::string &n, const proto::Machine_CardioType &t) {
	CardioMachine* result = (CardioMachine*)_cmProto.clone();
	result->_protoMachine.set_id(Machine::_nextId++);
	result->_protoMachine.set_name(n);
	result->_protoMachine.set_ctype(t);
	result->_startTime = -1;
	result->_resistance = 0;

	return result;
}

/** 
* The new machine will be given a new ID, and default values for startTime (-1), repetitions (0), and weight(0).
*/
WeightMachine* MachineFactory::createWeightMachine(const std::string &n, const proto::Machine_WeightType &t) {
	WeightMachine* result = (WeightMachine*)_wmProto.clone();
	result->_protoMachine.set_id(Machine::_nextId++);
	result->_protoMachine.set_name(n);
	result->_protoMachine.set_wtype(t);
	result->_startTime = -1;
	result->_repetitions = 0;
	result->_weight = 0;

	return result;
}

/**
* The new machine will be given a new ID, and default values for startTime (-1), resistance(0), repetitions (0), and weight(0) as appropriate.
*/
Machine* MachineFactory::createMachine(const proto::Machine &m) {
	Machine* result;
	// Either ctype exists (in which case we want a cardio machine)
	// or else wtype exists (in which case we want a weight machine).
	if (m.ctype()) {
		result = _cmProto.clone();
		result->_protoMachine = m;
		((CardioMachine*)result)->_startTime = -1;
		((CardioMachine*)result)->_resistance = 0;
	}
	else {
		result = _wmProto.clone();
		result->_protoMachine = m;
		((WeightMachine*)result)->_startTime = -1;
		((WeightMachine*)result)->_repetitions = 0;
		((WeightMachine*)result)->_weight = 0;
	}
	// Set to use the next available ID.
	result->_protoMachine.set_id(Machine::_nextId++);
	return result;
}