/** 
 * File:   fsm.h
 *
 * Class contains the controlling FSM for sorting out metal contaminated parts.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-01
 */

#ifndef FSM_H
#define	FSM_H
#include "FestoProcessAccess.h"
#include "Plugin.h"
#include "test/FSMTest.h"

enum class FSMStates { START, STANDBY, READY, TRANSPORT, HEIGHT_MEASURE, PART_OK, PART_BAD, START_REACHED, ERROR, END_REACHED};

class FSM {
    friend class FSMTest;
private:
    FSMStates currentState;
    FestoProcessAccess *process;
    Plugin* plugin;
public:
    FSM( FestoProcessAccess *process, Plugin* plugin);
    ~FSM();
    void eval();
private:
    void evalEvents();
    void evalState();
private:
    void blinkGreen();
    void blinkRed();
    void blinkYellow();
};

#endif	/* FSM_H */

