#include "stdafx.h"
#include "CardioMachine.h"


CardioMachine::CardioMachine(const std::string &name, const CardioMachineType &t) :
	Machine(name),
	_type(t),
	_startTime(-1),
	_resistance(0) {
}

CardioMachine::CardioMachine(const CardioMachine &c) :
	Machine(c),
	_type(c.getType()),
	_startTime(c._startTime),
	_resistance(c._resistance){
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
	switch (_type) {
	case Treadmill:
		return "Treadmill";
	case Elliptical:
		return "Eliptical";
	case StationaryBike:
		return "Stationary Bike";
	default:
		return "";
	}
}

/**
* CardioMachine specific methods
*/

CardioMachine::CardioMachineType CardioMachine::getType() const {
	return _type;
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

CardioMachine::CardioMachineType CardioMachine::parseTypeFromString(const std::string &t) {
	std::string tlc;
	// Transform the string to lower case
	std::transform(t.begin(), t.end(), std::back_inserter(tlc), ::tolower);

	if (tlc == "treadmill") {
		return CardioMachine::CardioMachineType(Treadmill);
	}
	else if (tlc == "elliptical") {
		return CardioMachine::CardioMachineType(Elliptical);
	}
	else if (tlc == "stationarybike" || tlc == "stationary bike") {
		return CardioMachine::CardioMachineType(StationaryBike);
	}
	return CardioMachine::CardioMachineType();
}