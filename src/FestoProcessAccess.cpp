/**
 * File:   FestoProcessAccess.cpp
 * 
 * Class providing high level access to sensors and actuators of the FESTO
 * system.
 *
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-01
 */

#include "iomasks.h"
#include "FestoProcessAccess.h"
#include <time.h>

FestoProcessAccess::FestoProcessAccess(FestoProcessImage* processImage) {
    timeCounter = 0;
    process = processImage;
    
#ifdef LOG_PROCESS
    logFile = fopen("c:\\tmp\\processlog.txt","w");
#else
    logFile = NULL;
#endif

}

FestoProcessAccess::~FestoProcessAccess() {
    delete process;
    if(logFile!=NULL){
        fclose(logFile);
    }
}

void FestoProcessAccess::updateInputs(void) {
    timeCounter = time(NULL);
    process->updateProcessImage();
    logProcessData();
}
void FestoProcessAccess::logProcessData(){
    if(logFile!=NULL){
        fprintf(logFile,"%i; %i; %i\n", (int)timeCounter1s(), isItemAtHightSensor(), getHight());
        fflush(logFile);
    }
}

void FestoProcessAccess::applyOutput(void) {
    process->applyOutputToProcess();
}

void FestoProcessAccess::driveRight(void) {
    process->setBitInOutput(DRIVE_DIRECTION_RIGHT);
    process->clearBitInOutput(DRIVE_STOP);
}

void FestoProcessAccess::driveLeft(void) {
    process-> setBitInOutput(DRIVE_DIRECTION_LEFT);
    process-> clearBitInOutput(DRIVE_STOP);
}

void FestoProcessAccess::driveSlowRight(void) {
    process->setBitInOutput(DRIVE_DIRECTION_RIGHT | DRIVE_SLOW);
    process->clearBitInOutput(DRIVE_STOP);
}

void FestoProcessAccess::driveSlowLeft(void) {
    process->setBitInOutput(DRIVE_DIRECTION_LEFT | DRIVE_SLOW);
    process->clearBitInOutput(DRIVE_STOP);
}

void FestoProcessAccess::driveStop(void) {
    process->clearBitInOutput(DRIVE_DIRECTION_LEFT | DRIVE_DIRECTION_RIGHT | DRIVE_SLOW);
    process->setBitInOutput(DRIVE_STOP);
}

void FestoProcessAccess::openJunction(void) {
    process->setBitInOutput(JUNCTION_OPEN);
}

void FestoProcessAccess::closeJunction(void) {
    process->clearBitInOutput(JUNCTION_OPEN);
}

void FestoProcessAccess::lightGreenOn(void) {
    process->setBitInOutput(TRAFIC_LIGHT_GREEN);
}

void FestoProcessAccess::lightGreenOff(void) {
    process->clearBitInOutput(TRAFIC_LIGHT_GREEN);
}

void FestoProcessAccess::lightYellowOn(void) {
    process->setBitInOutput(TRAFIC_LIGHT_YELLOW);
}

void FestoProcessAccess::lightYellowOff(void) {
    process->clearBitInOutput(TRAFIC_LIGHT_YELLOW);
}

void FestoProcessAccess::lightRedOn(void) {
    process->setBitInOutput(TRAFIC_LIGHT_RED);
}

void FestoProcessAccess::lightRedOff(void) {
    process->clearBitInOutput(TRAFIC_LIGHT_RED);
}

void FestoProcessAccess::turnLEDStartOn(void) {
    process->setBitInOutput(LED_START_BUTTON);
}

void FestoProcessAccess::turnLEDStartOff(void) {
    process->clearBitInOutput(LED_START_BUTTON);
}

void FestoProcessAccess::turnLEDResetOn(void) {
    process->setBitInOutput(LED_RESET_BUTTON);
};

void FestoProcessAccess::turnLEDResetOff(void) {
    process->clearBitInOutput(LED_RESET_BUTTON);
}

void FestoProcessAccess::turnLEDQ1On(void) {
    process->setBitInOutput(LED_Q1);
}

void FestoProcessAccess::turnLEDQ1Off(void) {
    process->clearBitInOutput(LED_Q1);
}

void FestoProcessAccess::turnLEDQ2On(void) {
    process->setBitInOutput(LED_Q2);
}

void FestoProcessAccess::turnLEDQ2Off(void) {
    process-> clearBitInOutput(LED_Q2);
}

void FestoProcessAccess::turnAllOff(void) {
    process->resetOutputs();
}

bool FestoProcessAccess::isItemAtBeginning(void) {
    return !(process->isBitSet(ITEM_DETECTED)); // active low
}

bool FestoProcessAccess::isItemAtHightSensor(void) {
    return !(process->isBitSet(ITEM_AT_HIGHT_SENSOR)); // active low
};

bool FestoProcessAccess::isItemAtMetalDetector(void) {
    return !(process->isBitSet(ITEM_AT_JUNCTION)); // active low
}

bool FestoProcessAccess::isMetalDetected(void) {
    return process->isBitSet(ITEM_IS_METTAL);
}

bool FestoProcessAccess::isJunctionOpen(void) {
    return process->isBitSet(JUNCTION_IS_OPEN);
}

bool FestoProcessAccess::isItemAtSlide(void) {
    return !(process->isBitSet(BUFFER_IS_FULL)); // active low
}
bool FestoProcessAccess::hasItemPassedSlide(void) {
    return (process->isBitPosEdge(BUFFER_IS_FULL)); // active low, so pos edge
}

bool FestoProcessAccess::isItemAtEnd(void) {
    return !(process->isBitSet(ITEM_AT_END)); // active low
}

bool FestoProcessAccess::isButtonStartPressed(void) {
    return process->isBitSet(BUTTON_START_PRESSED);
}

bool FestoProcessAccess::isButtonStartPositiveEdge(void) {
    return process->isBitPosEdge(BUTTON_START_PRESSED);
}

bool FestoProcessAccess::isButtonStartNegativeEdge(void) {
    return process->isBitNegEdge(BUTTON_START_PRESSED);
}

bool FestoProcessAccess::isButtonStopPressed(void) {
    return !(process->isBitSet(BUTTON_STOP_PRESSED)); // active low
}

bool FestoProcessAccess::isButtonResetPressed(void) {
    return process->isBitSet(BUTTON_RESET_PRESSED);
}

bool FestoProcessAccess::isButtonEmergencyActive(void) {
    return !(process->isBitSet(EMERGENCY_STOP_PRESSED)); // active low
}
unsigned short FestoProcessAccess::getHight(){
    return process->hight();
}

time_t FestoProcessAccess::timeCounter1s(){
    return time(NULL);
}