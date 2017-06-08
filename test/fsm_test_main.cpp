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

static FSM *fsm;
static DebugProcessImage *dpi;

void tearDown();
void setup();

bool performTest(Runnable test, const FSMStates& finalState);

void path1();


int main(){
    if(performTest(path1, FSMStates::STANDBY)){
        cout << "Pass" << endl;
    } else {
        cout << "Fail" << endl;
    }
    return 0;
}

void setup(){
    if(dpi || fsm){
        tearDown();
    }

    dpi = new DebugProcessImage();
    FestoProcessAccess *fpa = new FestoProcessAccess(dpi);
    fsm = new FSM(fpa, new LegoPartChecker(fpa));
}

void tearDown(){
    if(fsm){
        delete fsm;
        fsm = nullptr;
        dpi = nullptr;
    }
    if(dpi){
        dpi = nullptr;
    }
}

bool performTest(Runnable test, const FSMStates& finalState){
    setup();
    bool result = FSMTest::runTest(test, fsm, finalState);
    tearDown();
    return result;
}

void path1(){
    cout << "P1" << endl;
}
