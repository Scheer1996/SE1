/** ****************************************************************
 * @file    test/fsm_test_main.cpp
 ******************************************************************
 */

#include "FSMTest.h"
#include "src/DebugProcessImage.h"
#include "src/LegoPartChecker.h"
#include <iostream>

using std::cout;
using std::endl;

//TODO: docmentation
static FSM *fsm;
static DebugProcessImage *dpi;

void tearDown();
void setup();

void performTest(std::string name, Runnable test, const FSMStates& finalState);

void path1();

static constexpr auto RED = "\x1b[31m";
static constexpr auto GREEN = "\x1b[32m";
static constexpr auto RESET = "\033[0m";

static int counter = 0;
static int failed = 0;
static std::string failedStr = "";
static std::string delim = "";

int main() {
    // Run tests
    performTest("Path 1", path1, FSMStates::STANDBY);

    // Evaluation
    cout << "\n\n\n";
    cout << "--------------------------------------" << endl;
    cout << "Results:" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Total tests run: " << counter << " - ";
    if(failed > 0){
        if(failed == 1){
            cout << RED << "There was 1 failure" << RESET << endl;
        } else {
            cout << RED << "There were " << failed << " failures" << RESET << endl;
        }
        cout << "Following paths have failed:" << endl;
        cout << failedStr;
    } else {
        cout << GREEN << "All tests have passed! " << RESET << endl;
    }
    return 0;
}

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

    dpi->setHeight(0);

    dpi->updateProcessImage();
}

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

void performTest(std::string name, Runnable test, const FSMStates& finalState) {
    setup();
    bool result = FSMTest::runTest(test, fsm, finalState);
    tearDown();

    counter++;
    if (!result) {
        failedStr += delim + name;
        delim = ", ";
        failed++;
    }
}

/* *******************************************************
 * The test paths
 * **************************************************** */
void path1() {
    // Start, Standby, Ready, Standby

    fsm->eval(); //Standby
    dpi->setButtonStart(true);
    fsm->eval(); // Standby
    dpi->setButtonStart(false); //negative edge
    fsm->eval(); // Ready
    dpi->setButtonStart(true);
    fsm->eval(); // Ready
    dpi->setButtonStart(false); // negative edge
    fsm->eval(); // Standby
}
