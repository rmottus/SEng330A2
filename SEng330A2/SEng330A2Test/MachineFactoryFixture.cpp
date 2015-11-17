#include "MachineFactoryFixture.h"

MachineFactoryFixture::MachineFactoryFixture() : mFactory() {}

CardioMachine* MachineFactoryFixture::getCardioMachineCloner() const {
	return mFactory._cmProto;
}

WeightMachine* MachineFactoryFixture::getWeightMachineCloner() const {
	return mFactory._wmProto;
}