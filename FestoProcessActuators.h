/**
 * File:   FestoProcessActuators.h
 * 
 * Class providing access to actuators of the FESTO system.
 *
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2015-05-10
 */

#ifndef FESTO_ACTUATORS_H
#define FESTO_ACTUATORS_H

class FestoProcessActuators {
public:
    virtual void driveRight(void) = 0;
    virtual void driveLeft(void) = 0;
    virtual void driveSlowRight(void) = 0;
    virtual void driveSlowLeft(void) = 0;
    virtual void driveStop(void) = 0;
    virtual void openJunction(void) = 0;
    virtual void closeJunction(void) = 0;
    virtual void lightGreenOn(void) = 0;
    virtual void lightGreenOff(void) = 0;
    virtual void lightYellowOn(void) = 0;
    virtual void lightYellowOff(void) = 0;
    virtual void lightRedOn(void) = 0;
    virtual void lightRedOff(void) = 0;
    virtual void turnLEDStartOn(void) = 0;
    virtual void turnLEDStartOff(void) = 0;
    virtual void turnLEDResetOn(void) = 0;
    virtual void turnLEDResetOff(void) = 0;
    virtual void turnLEDQ1On(void) = 0;
    virtual void turnLEDQ1Off(void) = 0;
    virtual void turnLEDQ2On(void) = 0;
    virtual void turnLEDQ2Off(void) = 0;
    virtual void turnAllOff(void) = 0;
};

#endif	

