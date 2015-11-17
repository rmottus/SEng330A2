#include "stdafx.h"
#include "MachineFactory.h"

MachineFactory::MachineFactory() : _cmProto(nullptr), _wmProto(nullptr) {}

MachineFactory::~MachineFactory() {
	delete _cmProto;
	delete _wmProto;
}

CardioMachine* MachineFactory::createCardioMachine(const std::string &n, const proto::Machine_CardioType &t) {
	CardioMachine* result;
	if (_cmProto) {
		result = (CardioMachine*)_cmProto->clone();
		result->_protoMachine.set_id(Machine::_nextId++);
		result->_protoMachine.set_name(n);
		result->_protoMachine.set_ctype(t);
		result->_startTime = -1;
		result->_resistance = 0;
	}
	else {
		result = new CardioMachine(n, t);
		_cmProto = result;
	}

	return result;
}

WeightMachine* MachineFactory::createWeightMachine(const std::string &n, const proto::Machine_WeightType &t) {
	WeightMachine* result;
	if (_wmProto) {
		result = (WeightMachine*)_wmProto->clone();
		result->_protoMachine.set_id(Machine::_nextId++);
		result->_protoMachine.set_name(n);
		result->_protoMachine.set_wtype(t);
		result->_startTime = -1;
		result->_repetitions = 0;
		result->_weight = 0;
	}
	else {
		result = new WeightMachine(n, t);
		_wmProto = result;
	}

	return result;
}

Machine* MachineFactory::createMachine(const proto::Machine &m) {
	Machine* result;
	if (m.ctype()) {
		if (_cmProto) {
			result = _cmProto->clone();
			result->_protoMachine = m;
			((CardioMachine*)result)->_startTime = -1;
			((CardioMachine*)result)->_resistance = 0;
		}
		else {
			result = new CardioMachine(m);
			_cmProto = (CardioMachine*) result;
		}
	}
	else {
		if (_wmProto) {
			result = _wmProto->clone();
			result->_protoMachine = m;
			((WeightMachine*)result)->_startTime = -1;
			((WeightMachine*)result)->_repetitions = 0;
			((WeightMachine*)result)->_weight = 0;
		}
		else {
			result = new WeightMachine(m);
			_wmProto = (WeightMachine*)result;
		}
	}
	result->_protoMachine.set_id(Machine::_nextId++);
	return result;
}