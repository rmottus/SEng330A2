#include "stdafx.h"
#include "Machine.h"

int Machine::_nextId = 0;

Machine::Machine(const std::string &n) : _id(_nextId++), _name(n) {}

Machine::Machine(const Machine &m) : _id(_nextId++), _name(m.getName()) {}

const int Machine::getId() const {
	return _id;
}

std::string Machine::getName() const {
	return _name;
}