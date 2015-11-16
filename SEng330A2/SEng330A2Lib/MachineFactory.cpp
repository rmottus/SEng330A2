#include "stdafx.h"
#include "MachineFactory.h"

MachineFactory::MachineFactory() : _cmProto(nullptr), _wmProto(nullptr) {}

MachineFactory::~MachineFactory() {
	delete _cmProto;
	delete _wmProto;
}

Machine* MachineFactory::createCardioMachine(const std::string &n, const proto::Machine_CardioType &t) {
	Machine* result;
	if (_cmProto) {
		result = _cmProto->clone();
		result->_protoMachine.set_id(Machine::_nextId++);
		result->_protoMachine.set_name(n);
		result->_protoMachine.set_ctype(t);
	}
	else {
		result = new CardioMachine(n, t);
		_cmProto = result;
	}

	return result;
}

Machine* MachineFactory::createWeightMachine(const std::string &n, const proto::Machine_WeightType &t) {
	Machine* result;
	if (_wmProto) {
		result = _wmProto->clone();
		result->_protoMachine.set_id(Machine::_nextId++);
		result->_protoMachine.set_name(n);
		result->_protoMachine.set_wtype(t);
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
		}
		else {
			result = new CardioMachine(m);
			_cmProto = result;
		}
	}
	else {
		if (_wmProto) {
			result = _wmProto->clone();
			result->_protoMachine = m;
					}
		else {
			result = new WeightMachine(m);
			_wmProto = result;
		}
	}
	result->_protoMachine.set_id(Machine::_nextId++);
	return result;
}