/** 
 * File:   fsm.cpp
 *
 * Class contains the controlling FSM for sorting out metal contaminated parts.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-01
 */

#include "FSM.h"

FSM::FSM(FestoProcessAccess *process, Plugin* plugin = 0) {
    this->process = process;
    currentState = FSMStates::START;
    this->plugin = plugin;
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
            if (process->isItemAtBeginning()&& !process->isItemAtEnd()) {
                currentState = FSMStates::TRANSPORT;
            }
            if (process->isItemAtHeightSensor() || process->isItemAtMetalDetector()) {
                currentState = FSMStates::ERROR;
            }
            break;
        case FSMStates::TRANSPORT:
            if (process->isItemAtMetalDetector()) {
                //TODO: currentState = MetalDetection;
            }
            if (process->isItemAtEnd()) {
                currentState = FSMStates::ERROR;
            }
            break;
        case FSMStates::HEIGHT_MEASURE:
            if (process->isMetalDetected()) {
                // currentState = Metalic;
            } else {
                //currentState = NonMetalic;
            }
            break;
        case FSMStates::PART_OK:
            if (process->isItemAtEnd()) {
                //currentState = EndReached;
            }
            if (process->isItemAtBeginning() || process->isItemAtHeightSensor()) {
                //currentState = Error;
            }
            break;
        case FSMStates::END_REACHED:
            if (process->isButtonStartNegativeEdge()) {
                currentState = FSMStates::START;
            }
            if (!(process->isItemAtEnd())) {
                currentState = FSMStates::READY;
            }
            if (process->isItemAtMetalDetector() || process->isItemAtHeightSensor()) {
                currentState = FSMStates::ERROR;
            }
            break;
        case FSMStates::PART_BAD:
            if (process->hasItemPassedSlide()) {
                //currentState = SlideReached;
            }
            if (process->isItemAtBeginning() || process->isItemAtHeightSensor()) {
                //currentState = Error;
            }
            break;
        case FSMStates::START_REACHED:
            if (process->isButtonStartNegativeEdge()) {
                //currentState = Standby;
            }
            if (process->isItemAtBeginning()) {
                //currentState = Transport;
            }
            if (process->isItemAtEnd() || process->isItemAtHeightSensor()) {
                //currentState = Error;
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
            process->driveRight();
            process->turnLightGreenOn();
            process->turnLightRedOff();
            process->turnLightYellowOff();
            process->turnLEDStartOff();
            break;
        case FSMStates::HEIGHT_MEASURE:
            process->driveStop();
            process->turnLightGreenOn();
            process->turnLightRedOff();
            process->turnLightYellowOff();
            break;
        case FSMStates::PART_OK:
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
            process->turnLEDStartOff();
            process->closeJunction();
            process->turnLEDStartOn();
            blinkGreen();
            break;
        case FSMStates::PART_BAD:
            process->driveRight();
            process->turnLightGreenOff();
            process->turnLightRedOff();
            process->turnLightYellowOn();
            break;
        case FSMStates::START_REACHED:
            process->driveStop();
            process->turnLightGreenOn();
            process->turnLightRedOff();
            process->turnLightYellowOff();
            process->turnLEDStartOn();
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
