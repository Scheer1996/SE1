/**
 * File:   FestoProcessAccess.h
 * 
 * Class providing high level access to sensors and actuators of the FESTO
 * system.
 *
 * \author   Prof. Dr. Thomas Lehmann
 * \version  2
 * \date     2013-11-01
 * \modified 2015-05-10
 */

#ifndef FESTO_PROCESS_ACCESS_H
#define FESTO_PROCESS_ACCESS_H

#include <cstdio>

#include "FestoProcessSensors.h"
#include "FestoProcessActuators.h"
#include "processimage.h"

#define LOG_PROCESS

/* Facade as delegate*/
class FestoProcessAccess : public FestoProcessSensors, FestoProcessActuators {
private:
    time_t timeCounter;
    FestoProcessImage* process;
    FILE* logFile;

public:
    FestoProcessAccess(FestoProcessImage* processImage);
    virtual ~FestoProcessAccess();
public:
    void updateInputs(void);
    void applyOutput(void);
public:
    virtual void driveRight(void);
    virtual void driveLeft(void);
    virtual void driveSlowRight(void);
    virtual void driveSlowLeft(void);
    virtual void driveStop(void);
    virtual void openJunction(void);
    virtual void closeJunction(void);
    virtual void lightGreenOn(void);
    virtual void lightGreenOff(void);
    virtual void lightYellowOn(void);
    virtual void lightYellowOff(void);
    virtual void lightRedOn(void);
    virtual void lightRedOff(void);
    virtual void turnLEDStartOn(void);
    virtual void turnLEDStartOff(void);
    virtual void turnLEDResetOn(void);
    virtual void turnLEDResetOff(void);
    virtual void turnLEDQ1On(void);
    virtual void turnLEDQ1Off(void);
    virtual void turnLEDQ2On(void);
    virtual void turnLEDQ2Off(void);
    virtual void turnAllOff(void);

    virtual bool isItemAtBeginning(void);
    virtual bool isItemAtHightSensor(void);
    virtual bool isItemAtMetalDetector(void);
    virtual bool isMetalDetected(void);
    virtual bool isJunctionOpen(void);
    virtual bool isItemAtSlide(void);
    virtual bool hasItemPassedSlide(void);
    virtual bool isItemAtEnd(void);
    virtual bool isButtonStartPressed(void);
    virtual bool isButtonStartPositiveEdge(void);
    virtual bool isButtonStartNegativeEdge(void);
    virtual bool isButtonStopPressed(void);
    virtual bool isButtonResetPressed(void);
    virtual bool isButtonEmergencyActive(void);
    virtual unsigned short getHight();

    virtual time_t timeCounter1s();
private:
    void logProcessData();
};

#endif	

