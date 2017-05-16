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
#include "plugin.h"

enum fsm_states { Start, Standby, Ready, Transport, MetalDetection, NonMetalic, Metalic, SlideReached, Error, EndReached};

class FSM {
private:
    fsm_states currentState;
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
};

#endif	/* FSM_H */

