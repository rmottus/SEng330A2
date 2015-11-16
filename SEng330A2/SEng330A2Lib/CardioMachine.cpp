#include "stdafx.h"
#include "CardioMachine.h"


CardioMachine::CardioMachine(const std::string &name, const proto::Machine_CardioType &t) :
	Machine(name),
	_startTime(-1),
	_resistance(0) {
	_protoMachine.set_ctype(t);
}

CardioMachine::CardioMachine(const CardioMachine &c) :
	Machine(c),
	_startTime(c._startTime),
	_resistance(c._resistance){
}

CardioMachine::CardioMachine(const proto::Machine &m) :
	Machine(m),
	_startTime(-1),
	_resistance(0){
}

/**
* Methods to inherited from Machine
*/

void CardioMachine::beginWorkout() {
	// Start time = current time
	_startTime = time(0);
}

void CardioMachine::endWorkout() {
	// TODO add usage statistic
	_startTime = -1;
}

Machine* CardioMachine::clone() {
	return new CardioMachine(*this);
}

std::string CardioMachine::getTypeString() {
	switch (_protoMachine.ctype()) {
	case proto::Machine_CardioType::Machine_CardioType_TREADMILL:
		return "Treadmill";
	case proto::Machine_CardioType::Machine_CardioType_ELLIPTICAL:
		return "Eliptical";
	case proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE:
		return "Stationary Bike";
	default:
		return "";
	}
}

/**
* CardioMachine specific methods
*/

proto::Machine_CardioType CardioMachine::getType() const {
	return _protoMachine.ctype();
}

void CardioMachine::increaseResistance() {
	if (_resistance < 5) 
		_resistance++;
}

void CardioMachine::decreaseResistance() {
	if (_resistance > 0) 
		_resistance--;
}

/**
* Static methods
*/

proto::Machine_CardioType CardioMachine::parseTypeFromString(const std::string &t) {
	std::string tlc;
	// Transform the string to lower case
	std::transform(t.begin(), t.end(), std::back_inserter(tlc), ::tolower);

	if (tlc == "treadmill") {
		return proto::Machine_CardioType(proto::Machine_CardioType::Machine_CardioType_TREADMILL);
	}
	else if (tlc == "elliptical") {
		return proto::Machine_CardioType(proto::Machine_CardioType::Machine_CardioType_ELLIPTICAL);
	}
	else if (tlc == "stationarybike" || tlc == "stationary bike") {
		return proto::Machine_CardioType(proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE);
	}
	return proto::Machine_CardioType();
}