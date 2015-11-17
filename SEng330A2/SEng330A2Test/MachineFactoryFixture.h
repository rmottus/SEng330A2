#pragma once

#include "MachineFactory.h"
#include "gtest/gtest.h"

class MachineFactoryFixture : public ::testing::Test {
public:
	MachineFactoryFixture();
	~MachineFactoryFixture() {};

	MachineFactory mFactory;
	CardioMachine* getCardioMachineCloner() const;
	WeightMachine* getWeightMachineCloner() const;
};