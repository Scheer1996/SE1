/** ****************************************************************
 * @file    test/fsm_test_main.cpp
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    14.06.2017
 ******************************************************************
 */
#include "FSMTest.h"
#include "src/DebugProcessImage.h"
#include "src/LegoPartChecker.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "src/config.h"

using std::cout;
using std::endl;
using namespace std::chrono;

// test framework
void tearDown();
void setup();
void performTest(std::string name, Runnable test, const FSMStates& finalState);

// test paths
void fromStartToReady();
void path1();
void path2();
void path3();
void path4();
void path5();
void path6();
void path7();
void path8();
void path9();
void path10();
void path11();
void path12();

// colors for output
static constexpr auto RED = "\x1b[31m";
static constexpr auto GREEN = "\x1b[32m";
static constexpr auto RESET = "\033[0m";

static FSM *fsm; ///< pointer to current FSM
static DebugProcessImage *dpi; ///< Pointer to current process image
static int counter = 0; ///< how many tests have been run
static int failed = 0; ///< how many tests have failed
static std::string failedStr = ""; ///< buffer for storing which tests have failed
static std::string delim = ""; ///< for fancy printing of buffer

int main() {
    // Run tests
    performTest("From Start to Ready", fromStartToReady, FSMStates::READY);
    performTest("Path 1", path1, FSMStates::STANDBY);
    performTest("Path 2", path2, FSMStates::STANDBY);
    performTest("Path 3", path3, FSMStates::READY);
    performTest("Path 4", path4, FSMStates::STANDBY);
    performTest("Path 5", path5, FSMStates::READY);
    performTest("Path 6", path6, FSMStates::STANDBY);
    performTest("Path 7", path7, FSMStates::ERROR);
    performTest("Path 8", path8, FSMStates::ERROR);
    performTest("Path 9", path9, FSMStates::ERROR);
    performTest("Path 10", path10, FSMStates::ERROR);
    performTest("Path 11", path11, FSMStates::ERROR);
    performTest("Path 12", path12, FSMStates::ERROR);

    // Evaluation
    cout << "\n\n\n";
    cout << "--------------------------------------" << endl;
    cout << "Results:" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Total tests run: " << counter << " - ";
    if (failed > 0) {
        if (failed == 1) {
            cout << RED << "There was 1 failure" << RESET << endl;
        } else {
            cout << RED << "There were " << failed << " failures" << RESET
                    << endl;
        }
        cout << "Following paths have failed:" << endl;
        cout << failedStr << endl;
    } else {
        cout << GREEN << "All tests have passed! " << RESET << endl;
    }
    return 0;
}

/**
 * Sets up the test environment.
 * Creates a new FSM and a new DebugProcessImage, and sets up inputs for the
 * DebugProcessImage
 */
void setup() {
    if (dpi || fsm) {
        tearDown();
    }

    dpi = new DebugProcessImage();
    FestoProcessAccess *fpa = new FestoProcessAccess(dpi);
    fsm = new FSM(fpa, new LegoPartChecker(fpa));

    dpi->setItemAtBeginning(false);
    dpi->setItemAtHeightSensor(false);
    dpi->setItemAtMetalDetection(false);
    dpi->setItemAtEnd(false);

    dpi->setButtonStart(false);
    dpi->setEmergencyStop(false);

    dpi->setHeight(BELT_HEIGHT);

    dpi->updateProcessImage();
}

/**
 * Cleans up the test environment.
 * Deletes the FSM
 */
void tearDown() {
    if (fsm) {
        delete fsm;
        fsm = nullptr;
        dpi = nullptr;
    }
    if (dpi) {
        dpi = nullptr;
    }
}

/**
 * Perform a test.
 * Will setup the test environment, run the test through TestFSM, evaluate the
 * result and clean up the test environment.
 *
 * @param name       name of the test (for error reporting)
 * @param test       the test to run
 * @param finalState the final state the FSM should be in after the test
 */
void performTest(std::string name, Runnable test, const FSMStates& finalState) {
    cout << "#################################" << endl;
    cout << "Running test " << name << endl;
    cout << "#################################" << endl;

    setup();
    bool result = FSMTest::runTest(test, fsm, finalState);
    tearDown();

    counter++;
    if (!result) {
        failedStr += delim + name;
        delim = ", "; // make sure that the failed paths are seperated by comma
        failed++;
    }
}

/* *******************************************************
 * The test paths
 * **************************************************** */
void fromStartToReady() {
    // Start, Standby, Ready

    fsm->eval(); //Standby
    dpi->setButtonStart(true);
    fsm->eval(); // Standby
    dpi->setButtonStart(false); //negative edge
    fsm->eval(); // Ready
}

void path1() {
    // Start, Standby, Ready, Standby

    fromStartToReady(); // Ready

    dpi->setButtonStart(true);
    fsm->eval(); // Ready
    dpi->setButtonStart(false); // negative edge
    fsm->eval(); // Standby
}

void path2() {
    // Start, Standby, Ready, Error, Standby

    fromStartToReady(); // Ready

    dpi->setItemAtHeightSensor(true);
    fsm->eval(); // Error

    dpi->setItemAtHeightSensor(false);
    dpi->setButtonStart(true);
    fsm->eval(); // Error
    dpi->setButtonStart(false); // negative edge
    fsm->eval(); // Standby

}

void path3() {
    // Start, Standby, Ready, Transport, Height Measure, Part Bad,
    // Start Reached, Ready

    fromStartToReady(); // Ready

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Transport

    dpi->setItemAtBeginning(false);
    dpi->setItemAtHeightSensor(true);
    dpi->setHeight(10);
    fsm->eval(); // HeightMeasure
    fsm->eval(); // HeightMeasure

    dpi->setItemAtHeightSensor(false);
    dpi->setHeight(BELT_HEIGHT);
    fsm->eval(); // Part Bad

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Start Reached

    dpi->setItemAtBeginning(false);
    fsm->eval(); // Ready

}

void path4() {
    // Start, Standby, Ready, Transport, Height Measure, Part Bad,
    // Start Reached, Standby

    fromStartToReady(); // Ready

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Transport

    dpi->setItemAtBeginning(false);
    dpi->setItemAtHeightSensor(true);
    dpi->setHeight(10);
    fsm->eval(); // HeightMeasure
    fsm->eval(); // HeightMeasure

    dpi->setItemAtHeightSensor(false);
    dpi->setHeight(BELT_HEIGHT);
    fsm->eval(); // Part Bad

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Start Reached

    dpi->setButtonStart(true);
    fsm->eval(); // StartReached

    dpi->setButtonStart(false); // negative edge
    fsm->eval(); // Standby

}

void path5() {
    // Start, Standby, Ready, Transport, Height Measure, Part OK,
    // End Reached, Ready

    fromStartToReady(); // Ready

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Transport

    dpi->setItemAtBeginning(false);
    dpi->setItemAtHeightSensor(true);
    dpi->setHeight(3414);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(432));
    dpi->setHeight(3720);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(456));
    dpi->setHeight(3418);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(480));
    dpi->setHeight(3114);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(456));
    dpi->setHeight(BELT_HEIGHT);
    fsm->eval(); // HeightMeasure

    dpi->setItemAtHeightSensor(false);
    fsm->eval(); // Part OK

    dpi->setItemAtEnd(true);
    fsm->eval(); // End Reached

    dpi->setItemAtEnd(false);
    fsm->eval(); // Ready

}

void path6() {
    // Start, Standby, Ready, Transport, Height Measure, Part Ok,
    // End Reached, Standby

    fromStartToReady(); // Ready

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Transport

    dpi->setItemAtBeginning(false);
    dpi->setItemAtHeightSensor(true);
    dpi->setHeight(3414);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(432));
    dpi->setHeight(3720);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(456));
    dpi->setHeight(3418);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(480));
    dpi->setHeight(3114);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(456));
    dpi->setHeight(BELT_HEIGHT);
    fsm->eval(); // HeightMeasure

    dpi->setItemAtHeightSensor(false);
    fsm->eval(); // Part OK

    dpi->setItemAtEnd(true);
    fsm->eval(); // End Reached

    dpi->setButtonStart(true);
    fsm->eval(); // End Reached

    dpi->setButtonStart(false); // negative edge
    fsm->eval(); // Standby

}

void path7() {
    // Start, Standby, Ready, Transport, Error

    fromStartToReady(); // Ready

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Transport

    dpi->setItemAtEnd(true);
    fsm->eval(); // Error

}

void path8() {
    // Start, Standby, Ready, Transport, Height Measure, Error
    fromStartToReady(); // Ready

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Transport

    dpi->setItemAtBeginning(false);
    dpi->setItemAtHeightSensor(true);
    dpi->setHeight(10);
    fsm->eval(); // HeightMeasure

    dpi->setItemAtEnd(true);
    fsm->eval(); // Error

}

void path9() {
    // Start, Standby, Ready, Transport, Height Measure, Part Bad,
    // Error

    fromStartToReady(); // Ready

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Transport

    dpi->setItemAtBeginning(false);
    dpi->setItemAtHeightSensor(true);
    dpi->setHeight(10);
    fsm->eval(); // HeightMeasure
    fsm->eval(); // HeightMeasure

    dpi->setItemAtHeightSensor(false);
    dpi->setHeight(BELT_HEIGHT);
    fsm->eval(); // Part Bad

    dpi->setItemAtEnd(true);
    fsm->eval(); // Error

}

void path10() {
    // Start, Standby, Ready, Transport, Height Measure, Part Ok,
    // Error

    fromStartToReady(); // Ready

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Transport

    dpi->setItemAtBeginning(false);
    dpi->setItemAtHeightSensor(true);
    dpi->setHeight(3414);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(432));
    dpi->setHeight(3720);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(456));
    dpi->setHeight(3418);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(480));
    dpi->setHeight(3114);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(456));
    dpi->setHeight(BELT_HEIGHT);
    fsm->eval(); // HeightMeasure

    dpi->setItemAtHeightSensor(false);
    fsm->eval(); // Part OK

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Error

}

void path11() {
    // Start, Standby, Ready, Transport, Height Measure, Part Bad,
    // Start Reached, Error

    fromStartToReady(); // Ready

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Transport

    dpi->setItemAtBeginning(false);
    dpi->setItemAtHeightSensor(true);
    dpi->setHeight(10);
    fsm->eval(); // HeightMeasure
    fsm->eval(); // HeightMeasure

    dpi->setItemAtHeightSensor(false);
    dpi->setHeight(BELT_HEIGHT);
    fsm->eval(); // Part Bad

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Start Reached

    dpi->setItemAtMetalDetection(true);
    fsm->eval(); // Error

}

void path12() {
    // Start, Standby, Ready, Transport, Height Measure, Part OK,
    // End Reached, Error

    fromStartToReady(); // Ready

    dpi->setItemAtBeginning(true);
    fsm->eval(); // Transport

    dpi->setItemAtBeginning(false);
    dpi->setItemAtHeightSensor(true);
    dpi->setHeight(3414);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(432));
    dpi->setHeight(3720);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(456));
    dpi->setHeight(3418);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(480));
    dpi->setHeight(3114);
    fsm->eval(); // HeightMeasure

    std::this_thread::sleep_for(milliseconds(456));
    dpi->setHeight(BELT_HEIGHT);
    fsm->eval(); // HeightMeasure

    dpi->setItemAtHeightSensor(false);
    fsm->eval(); // Part OK

    dpi->setItemAtEnd(true);
    fsm->eval(); // End Reached

    dpi->setItemAtMetalDetection(true);
    fsm->eval(); // Error

}
