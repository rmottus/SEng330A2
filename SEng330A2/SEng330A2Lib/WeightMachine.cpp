#include "stdafx.h"
#include "WeightMachine.h"

WeightMachine::WeightMachine(const std::string &n, const WeightMachine::WeightMachineType &t) :
	Machine(n),
	_type(t),
	_weight(0),
	_startTime(-1) {
}
	
WeightMachine::WeightMachine(const WeightMachine &w) :
	Machine(w),
	_type(w.getType()),
	_weight(w._weight),
	_startTime(w._startTime) {
}

/**
* Methods to inherited from Machine
*/

void WeightMachine::beginWorkout() {
	// Start time = current time
	_startTime = time(0);
}

void WeightMachine::endWorkout() {
	// TODO add usage statistic
	_startTime = -1;
}

Machine* WeightMachine::clone() {
	return new WeightMachine(*this);
}

std::string WeightMachine::getTypeString() {
	switch (_type) {
	case BenchPress:
		return "Bench Press";
	case PreacherCurl:
		return "Preacher Curl";
	case LegPress:
		return "Leg Press";
	default:
		return "";
	}
}

/**
* CardioMachine specific methods
*/

WeightMachine::WeightMachineType WeightMachine::getType() const {
	return _type;
}

void WeightMachine::setWeight(const int &new_weight) {
	if (new_weight > 0 && new_weight < 500) 
		_weight = new_weight;
}

/**
* Static methods
*/

WeightMachine::WeightMachineType WeightMachine::parseTypeFromString(const std::string &t) {
	std::string tlc;
	// Transform the string to lower case
	std::transform(t.begin(), t.end(), std::back_inserter(tlc), ::tolower);

	if (tlc == "benchpress" || tlc == "bench press") {
		return WeightMachine::WeightMachineType(BenchPress);
	}
	else if (tlc == "preachercurl" || tlc == "preacher curl") {
		return WeightMachine::WeightMachineType(PreacherCurl);
	}
	else if (tlc == "legpress" || tlc == "leg press") {
		return WeightMachine::WeightMachineType(LegPress);
	}
	return WeightMachine::WeightMachineType();
}