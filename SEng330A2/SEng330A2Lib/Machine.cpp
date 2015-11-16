#include "stdafx.h"
#include "Machine.h"

int Machine::_nextId = 0;

Machine::Machine(const std::string &n) : 
	_protoMachine() {
	_protoMachine.set_id(_nextId++);
	_protoMachine.set_name(n);
}

Machine::Machine(const Machine &m) : _protoMachine(m._protoMachine) {
	if (_protoMachine.id() > _nextId) {
		_nextId = _protoMachine.id() + 1;
	}
}

Machine::Machine(const proto::Machine &m) : _protoMachine(m) {
	if (_protoMachine.id() > _nextId) {
		_nextId = _protoMachine.id() + 1;
	}
}

const int Machine::getId() const {
	return _protoMachine.id();
}

std::string Machine::getName() const {
	return _protoMachine.name();
}

const proto::Machine Machine::getProtoMachine() const {
	return _protoMachine;
}