#include "stdafx.h"
#include "WeightMachine.h"

WeightMachine::WeightMachine(const std::string &n, const proto::Machine_WeightType &t) :
	Machine(n),
	_startTime(-1),
	_weight(0) {
	_protoMachine.set_wtype(t);
}
	
WeightMachine::WeightMachine(const WeightMachine &w) :
	Machine(w),
	_startTime(w._startTime),
	_weight(w._weight) {
}

WeightMachine::WeightMachine(const proto::Machine &m) :
	Machine(m),
	_startTime(-1),
	_weight(0) {
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
	switch (_protoMachine.wtype()) {
	case proto::Machine_WeightType::Machine_WeightType_BENCHPRESS:
		return "Bench Press";
	case proto::Machine_WeightType::Machine_WeightType_PREACHERCURL:
		return "Preacher Curl";
	case proto::Machine_WeightType::Machine_WeightType_LEGPRESS:
		return "Leg Press";
	default:
		return "";
	}
}

/**
* CardioMachine specific methods
*/

proto::Machine_WeightType WeightMachine::getType() const {
	return _protoMachine.wtype();
}

void WeightMachine::setWeight(const int &new_weight) {
	if (new_weight > 0 && new_weight < 500) 
		_weight = new_weight;
}

/**
* Static methods
*/

proto::Machine_WeightType WeightMachine::parseTypeFromString(const std::string &t) {
	std::string tlc;
	// Transform the string to lower case
	std::transform(t.begin(), t.end(), std::back_inserter(tlc), ::tolower);

	if (tlc == "benchpress" || tlc == "bench press") {
		return proto::Machine_WeightType(proto::Machine_WeightType::Machine_WeightType_BENCHPRESS);
	}
	else if (tlc == "preachercurl" || tlc == "preacher curl") {
		return proto::Machine_WeightType(proto::Machine_WeightType::Machine_WeightType_PREACHERCURL);
	}
	else if (tlc == "legpress" || tlc == "leg press") {
		return proto::Machine_WeightType(proto::Machine_WeightType::Machine_WeightType_LEGPRESS);
	}
	return proto::Machine_WeightType();
}