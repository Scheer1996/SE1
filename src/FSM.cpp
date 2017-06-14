/** 
 * @file FSM.cpp
 *
 * Class contains the controlling FSM for sorting out metal contaminated parts.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * @author Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 *
 * \version 1
 * \date    2013-11-01
 * @date    modified: 14.06.2017
 */

#include "FSM.h"

#include <cmath>

#include "config.h"

/**
 * should the state of the FSM be printed
 */
#define PRINT_STATE true

#if PRINT_STATE
#define LOGSTATE logState(currentState);
#include <iostream>
/**
 * Print the state.
 * will only print if the state changed
 *
 * @param state the current state
 */
void logState(FSMStates state) {
    using std::cout;
    using std::endl;

    static FSMStates lastState = FSMStates::ERROR;
    if (state == lastState) {
        return;
    }
    lastState = state;

    cout << "========================================" << endl;
    switch (state) {
        case FSMStates::START:
            cout << "START" << endl;
            break;
        case FSMStates::STANDBY:
            cout << "STANDBY" << endl;
            break;
        case FSMStates::READY:
            cout << "READY" << endl;
            break;
        case FSMStates::TRANSPORT:
            cout << "TRANSPORT" << endl;
            break;
        case FSMStates::HEIGHT_MEASURE:
            cout << "HEIGHT_MEASURE" << endl;
            break;
        case FSMStates::PART_OK:
            cout << "PART_OK" << endl;
            break;
        case FSMStates::END_REACHED:
            cout << "END_REACHED" << endl;
            break;
        case FSMStates::PART_BAD:
            cout << "PART_BAD" << endl;
            break;
        case FSMStates::START_REACHED:
            cout << "START_REACHED" << endl;
            break;
        case FSMStates::ERROR:
            cout << "ERROR" << endl;
            break;
    }
}
#else
#define LOGSTATE
#endif

FSM::FSM(FestoProcessAccess *process, Plugin* plugin = 0) {
    this->process = process;
    currentState = FSMStates::START;
    this->plugin = plugin;
    LOGSTATE
    ;
}

FSM::~FSM() {
    delete plugin;
    delete process;
}

void FSM::eval() {
    process->updateInputs();
    if (plugin) {
        plugin->evalCycle();
    }
    evalEvents();
    evalState();
    LOGSTATE
    ;
    process->applyOutput();
}

void FSM::evalEvents() {
    switch (currentState) {
        case FSMStates::START:
            currentState = FSMStates::STANDBY;
            break;
        case FSMStates::STANDBY:
            if (process->isButtonStartNegativeEdge()) {
                currentState = FSMStates::READY;
            }
            break;
        case FSMStates::READY:
            if (process->isButtonStartNegativeEdge()) {
                currentState = FSMStates::STANDBY;
            }
            if (process->isItemAtBeginning() && !process->isItemAtEnd()) {
                currentState = FSMStates::TRANSPORT;
            }
            if (process->isItemAtHeightSensor()
                    || process->isItemAtMetalDetector()) {
                currentState = FSMStates::ERROR;
            }
            break;
        case FSMStates::TRANSPORT:
            if (std::abs(process->getHeight() - BELT_HEIGHT)
                    > ALLOWED_HEIGHT_DEVIATION) {
                currentState = FSMStates::HEIGHT_MEASURE;
            }
            if (process->isItemAtEnd() || process->isItemAtMetalDetector()) {
                currentState = FSMStates::ERROR;
            }
            break;
        case FSMStates::HEIGHT_MEASURE:
            if (std::abs(process->getHeight() - BELT_HEIGHT)
                    < ALLOWED_HEIGHT_DEVIATION) {
                if (plugin->result()) {
                    currentState = FSMStates::PART_OK;
                } else {
                    currentState = FSMStates::PART_BAD;
                }
            }
            if (process->isItemAtEnd() || process->isItemAtMetalDetector()) {
                currentState = FSMStates::ERROR;
            }
            break;
        case FSMStates::PART_OK:
            if (process->isItemAtEnd()) {
                currentState = FSMStates::END_REACHED;
            }
            if (process->isItemAtBeginning()) {
                currentState = FSMStates::ERROR;
            }
            break;
        case FSMStates::END_REACHED:
            if (process->isButtonStartNegativeEdge()) {
                currentState = FSMStates::STANDBY;
            }
            if (!(process->isItemAtEnd())) {
                currentState = FSMStates::READY;
            }
            if (process->isItemAtMetalDetector()
                    || process->isItemAtHeightSensor()) {
                currentState = FSMStates::ERROR;
            }
            break;
        case FSMStates::PART_BAD:
            if (process->isItemAtBeginning()) {
                currentState = FSMStates::START_REACHED;
                plugin->result(); // reset measuring substate machine
            }
            if (process->isItemAtEnd() || process->isItemAtMetalDetector()) {
                currentState = FSMStates::ERROR;
            }
            break;
        case FSMStates::START_REACHED:
            if (process->isButtonStartNegativeEdge()) {
                currentState = FSMStates::STANDBY;
            }
            if (!process->isItemAtBeginning()) {
                currentState = FSMStates::READY;
            }
            if (process->isItemAtEnd() || process->isItemAtHeightSensor()
                    || process->isItemAtMetalDetector()) {
                currentState = FSMStates::ERROR;
            }
            break;
        case FSMStates::ERROR:
            if (process->isButtonStartNegativeEdge()) {
                currentState = FSMStates::STANDBY;
            }
            break;
        default:
            currentState = FSMStates::START;
    }
}

void FSM::evalState() {
    if (process->isButtonEmergencyActive()) {
        process->driveStop();
        process->turnLightGreenOff();
        process->turnLightYellowOff();
        process->closeJunction();
        blinkRed();
    } else {
        switch (currentState) {
            case FSMStates::START:
            case FSMStates::STANDBY:
                process->driveStop();
                process->turnLightGreenOff();
                process->turnLightRedOff();
                process->turnLightYellowOff();
                process->turnLEDQ1Off();
                process->turnLEDQ2Off();
                process->turnLEDResetOff();
                process->turnLEDStartOn();
                break;
            case FSMStates::READY:
                process->driveStop();
                process->turnLightGreenOn();
                process->turnLightRedOff();
                process->turnLightYellowOff();
                process->turnLEDStartOn();
                break;
            case FSMStates::TRANSPORT:
                process->driveSlowRight();
                process->turnLightGreenOn();
                process->turnLightRedOff();
                process->turnLightYellowOff();
                process->turnLEDStartOff();
                break;
            case FSMStates::HEIGHT_MEASURE:
                process->driveSlowRight();
                process->turnLightGreenOn();
                process->turnLightRedOff();
                process->turnLightYellowOff();
                break;
            case FSMStates::PART_OK:
                process->driveStop();
                process->driveRight();
                process->turnLightGreenOn();
                process->turnLightRedOff();
                process->turnLightYellowOff();
                process->turnLEDStartOff();
                process->openJunction();
                break;
            case FSMStates::END_REACHED:
                process->driveStop();
                process->turnLightRedOff();
                process->turnLightYellowOff();
                process->closeJunction();
                process->turnLEDStartOn();
                blinkGreen();
                break;
            case FSMStates::PART_BAD:
                process->driveStop();
                process->driveLeft();
                process->turnLightGreenOff();
                process->turnLightRedOff();
                process->turnLightYellowOn();
                break;
            case FSMStates::START_REACHED:
                process->driveStop();
                process->turnLightGreenOff();
                process->turnLightRedOff();
                process->turnLEDStartOn();
                blinkYellow();
                break;
            case FSMStates::ERROR:
                process->driveStop();
                process->turnLightGreenOff();
                process->turnLightYellowOff();
                process->turnLEDStartOn();
                process->closeJunction();
                blinkRed();
                break;

        }
    }
}

void FSM::blinkRed() {
    if (process->timeCounter1s() & 0x01) {
        process->turnLightRedOn();
    } else {
        process->turnLightRedOff();
    }
}

void FSM::blinkGreen() {
    if (process->timeCounter1s() & 0x01) {
        process->turnLightGreenOn();
    } else {
        process->turnLightGreenOff();
    }
}

void FSM::blinkYellow() {
    if (process->timeCounter1s() & 0x01) {
        process->turnLightYellowOn();
    } else {
        process->turnLightYellowOff();
    }
}
