/** @file SEng330A2Test.cpp
* The main entry point for the tests.
* Runs all tests, reporting any errors, then waits for user input before exiting.
*/

#include "stdafx.h"
#include "MachineFactory.h"
#include "CardioMachine.h"
#include "WeightMachine.h"
#include "MachineList.pb.h"

#include <stdio.h>
#include <tchar.h>
#include "gtest/gtest.h"

/** 
* Test that cloning CardioMachines works as expected (ie all values are left unchanged). 
*/
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

	// Changing one should not effect the other
	c.increaseResistance();
	EXPECT_NE(c.getResistance(), cClone->getResistance());
}

/**
* Test that cloning WeightMachines works as expected (ie all values are left unchanged).
*/
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

	// Changing one should not effect the other
	w.doRep();
	EXPECT_NE(w.getReps(), wClone->getReps());
}

/**
* Test that the strings for cardio machine types are parsed correctly.
* Also tests that an invalid string returns an invalid type.
*/
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

	EXPECT_EQ(proto::Machine_CardioType(), CardioMachine::parseTypeFromString("benchpress"));
}

/**
* Test that the strings for weight machine types are parsed correctly.
* Also tests that an invalid string returns an invalid type.
*/
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

	EXPECT_EQ(proto::Machine_WeightType(), WeightMachine::parseTypeFromString("treadmill"));
}

/** 
* Tests that the MachineFactory creats machines in a way that we expect when given a type directly.
*/
TEST(TEST_MACHINE_FACTORY, TEST_MACHINE_FACTORY_ENUM) {
	MachineFactory mFactory;
	CardioMachine* cm = mFactory.createCardioMachine("Lucky Charms", proto::Machine_CardioType::Machine_CardioType_TREADMILL);
	EXPECT_EQ("Lucky Charms", cm->getName());
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_TREADMILL, cm->getType());
	// Default  values
	EXPECT_EQ(-1, cm->getStartTime());
	EXPECT_EQ(0, cm->getResistance());

	// Modify CM
	cm->beginWorkout();
	cm->increaseResistance();

	CardioMachine* secondCM = mFactory.createCardioMachine("Honey Bunches of Oats", proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE);
	EXPECT_EQ("Honey Bunches of Oats", secondCM->getName());
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_STATIONARYBIKE, secondCM->getType());
	// These should still be default  values.
	EXPECT_EQ(-1, secondCM->getStartTime());
	EXPECT_EQ(0, secondCM->getResistance());

	WeightMachine* wm = mFactory.createWeightMachine("Fruit Loops", proto::Machine_WeightType::Machine_WeightType_LEGPRESS);
	EXPECT_EQ("Fruit Loops", wm->getName());
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_LEGPRESS, wm->getType());
	// Default values
	EXPECT_EQ(-1, wm->getStartTime());
	EXPECT_EQ(0, wm->getWeight());
	EXPECT_EQ(0, wm->getReps());

	// Modify WM
	wm->beginWorkout();
	wm->setWeight(100);
	wm->doRep();
	wm->doRep();

	WeightMachine* secondWM = mFactory.createWeightMachine("Cocoa Puffs", proto::Machine_WeightType::Machine_WeightType_BENCHPRESS);
	EXPECT_EQ("Cocoa Puffs", secondWM->getName());
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_BENCHPRESS, secondWM->getType());
	// Should still be default
	EXPECT_EQ(-1, secondWM->getStartTime());
	EXPECT_EQ(0, secondWM->getWeight());
	EXPECT_EQ(0, secondWM->getReps());
}

/**
* Tests that the MachineFactory creats machines in a way that we expect when given a protobuffer object.
*/
TEST(TEST_MACHINE_FACTORY, TEST_MACHINE_FACTORY_PROTO) {
	MachineFactory mFactory;
	proto::Machine protoM;
	protoM.set_name("Lucky Charms");
	protoM.set_id(100);
	protoM.set_ctype(proto::Machine_CardioType::Machine_CardioType_TREADMILL);

	CardioMachine* cm = (CardioMachine*) mFactory.createMachine(protoM);
	EXPECT_EQ("Lucky Charms", cm->getName());
	EXPECT_EQ(proto::Machine_CardioType::Machine_CardioType_TREADMILL, cm->getType());
	// Default  values
	EXPECT_EQ(-1, cm->getStartTime());
	EXPECT_EQ(0, cm->getResistance());

	protoM.set_name("Fruit Loops");
	protoM.set_id(100);
	protoM.set_wtype(proto::Machine_WeightType::Machine_WeightType_LEGPRESS);

	WeightMachine* wm = (WeightMachine*) mFactory.createMachine(protoM);
	EXPECT_EQ("Fruit Loops", wm->getName());
	EXPECT_EQ(proto::Machine_WeightType::Machine_WeightType_LEGPRESS, wm->getType());
	// Default values
	EXPECT_EQ(-1, wm->getStartTime());
	EXPECT_EQ(0, wm->getWeight());
	EXPECT_EQ(0, wm->getReps());
}

/** 
* Main entry point for the tests.
* Initiallizes the test, then runs them.
* Once they complete, it pauses and waits for the user to press a button so that they can read the results.
*/
int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("PAUSE");
}

