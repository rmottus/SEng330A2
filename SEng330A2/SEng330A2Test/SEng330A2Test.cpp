// SEng330A2Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MachineFactoryFixture.h"

#include <stdio.h>
#include <tchar.h>
#include "gtest/gtest.h"

TEST(TEST_CLONING, TEST_CARDIO_CLONING) {
	CardioMachine c("Test Cardio Machine", proto::Machine_CardioType::Machine_CardioType_ELLIPTICAL);
	c.increaseResistance();
	c.beginWorkout();
	CardioMachine* cClone = (CardioMachine *)c.clone();

	EXPECT_EQ(c.getName(), cClone->getName());
	EXPECT_EQ(c.getId(), cClone->getId());
	EXPECT_EQ(c.getType(), cClone->getType());
	EXPECT_EQ(c.getResistance(), cClone->getResistance());
	EXPECT_EQ(c.getStartTime(), cClone->getStartTime());
}

TEST(TEST_CLONING, TEST_WEIGHT_CLONING) {
	WeightMachine w("Test Weight Machine", proto::Machine_WeightType::Machine_WeightType_BENCHPRESS);
	w.beginWorkout();
	w.setWeight(100);
	w.doRep();
	WeightMachine* wClone = (WeightMachine *)w.clone();

	EXPECT_EQ(w.getName(), wClone->getName());
	EXPECT_EQ(w.getId(), wClone->getId());
	EXPECT_EQ(w.getTypeString(), wClone->getTypeString());
	EXPECT_EQ(w.getWeight(), wClone->getWeight());
	EXPECT_EQ(w.getReps(), wClone->getReps());
	EXPECT_EQ(w.getStartTime(), wClone->getStartTime());
}

TEST(TEST_TYPE_FROM_STRING, TEST_CARDIO_TYPE_FROM_STRING) {
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_ELLIPTICAL, CardioMachine::parseTypeFromString("elliptical"));
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_ELLIPTICAL, CardioMachine::parseTypeFromString("Elliptical"));

	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE, CardioMachine::parseTypeFromString("stationarybike"));
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE, CardioMachine::parseTypeFromString("Stationarybike"));
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE, CardioMachine::parseTypeFromString("StationaryBike"));
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE, CardioMachine::parseTypeFromString("stationary bike"));
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE, CardioMachine::parseTypeFromString("Stationary bike"));
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE, CardioMachine::parseTypeFromString("Stationary Bike"));

	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_TREADMILL, CardioMachine::parseTypeFromString("treadmill"));
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_TREADMILL, CardioMachine::parseTypeFromString("Treadmill"));
}

TEST(TEST_TYPE_FROM_STRING, TEST_WEIGHT_TYPE_FROM_STRING) {
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_BENCHPRESS, WeightMachine::parseTypeFromString("benchpress"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_BENCHPRESS, WeightMachine::parseTypeFromString("Benchpress"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_BENCHPRESS, WeightMachine::parseTypeFromString("BenchPress"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_BENCHPRESS, WeightMachine::parseTypeFromString("bench press"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_BENCHPRESS, WeightMachine::parseTypeFromString("Bench press"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_BENCHPRESS, WeightMachine::parseTypeFromString("Bench Press"));

	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_LEGPRESS, WeightMachine::parseTypeFromString("legpress"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_LEGPRESS, WeightMachine::parseTypeFromString("Legpress"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_LEGPRESS, WeightMachine::parseTypeFromString("LegPress"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_LEGPRESS, WeightMachine::parseTypeFromString("leg press"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_LEGPRESS, WeightMachine::parseTypeFromString("Leg press"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_LEGPRESS, WeightMachine::parseTypeFromString("Leg Press"));

	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_PREACHERCURL, WeightMachine::parseTypeFromString("preachercurl"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_PREACHERCURL, WeightMachine::parseTypeFromString("Preachercurl"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_PREACHERCURL, WeightMachine::parseTypeFromString("PreacherCurl"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_PREACHERCURL, WeightMachine::parseTypeFromString("preacher curl"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_PREACHERCURL, WeightMachine::parseTypeFromString("Preacher curl"));
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_PREACHERCURL, WeightMachine::parseTypeFromString("Preacher Curl"));
}

TEST_F(MachineFactoryFixture, TEST_MACHINE_FACTORY) {
	EXPECT_EQ(nullptr, getCardioMachineCloner());

	CardioMachine* cm = mFactory.createCardioMachine("Lucky Charms", proto::Machine_CardioType::Machine_CardioType_TREADMILL);
	proto::Machine pm = cm->getProtoMachine();

	EXPECT_EQ("Lucky Charms", pm.name());
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_TREADMILL, pm.ctype());
	EXPECT_EQ(-1, cm->getStartTime());
	EXPECT_EQ(0, cm->getResistance());
	EXPECT_EQ(cm, getCardioMachineCloner());

	cm->beginWorkout();
	cm->increaseResistance();

	CardioMachine* secondCM = mFactory.createCardioMachine("Honey Bunches of Oats", proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE);
	pm = secondCM->getProtoMachine();
	EXPECT_EQ("Honey Bunches of Oats", pm.name());
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE, pm.ctype());
	// These should still be default  values.
	EXPECT_EQ(-1, secondCM->getStartTime());
	EXPECT_EQ(0, secondCM->getResistance());
	// Pointer should still be to the first one added.
	EXPECT_EQ(cm, getCardioMachineCloner());

	EXPECT_EQ(nullptr, getWeightMachineCloner());
	WeightMachine* wm = mFactory.createWeightMachine("Fruit Loops", proto::Machine_WeightType::Machine_WeightType_LEGPRESS);
	pm = wm->getProtoMachine();

	EXPECT_EQ("Fruit Loops", pm.name());
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_LEGPRESS, pm.wtype());
	EXPECT_EQ(-1, wm->getStartTime());
	EXPECT_EQ(0, wm->getWeight());
	EXPECT_EQ(0, wm->getReps());
	EXPECT_EQ(wm, getWeightMachineCloner());

	WeightMachine* secondWM = mFactory.createWeightMachine("Cocoa Puffs", proto::Machine_WeightType::Machine_WeightType_BENCHPRESS);
	pm = secondWM->getProtoMachine();

	EXPECT_EQ("Cocoa Puffs", pm.name());
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_BENCHPRESS, pm.wtype());
	EXPECT_EQ(-1, wm->getStartTime());
	EXPECT_EQ(0, wm->getWeight());
	EXPECT_EQ(0, wm->getReps());
	EXPECT_EQ(wm, getWeightMachineCloner());
}

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
}

