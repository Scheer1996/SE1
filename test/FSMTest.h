/** ****************************************************************
 * @file    FSMTest.h 
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    08.06.2017
 * @brief   Wrapper for running state based tests (friend of FSM)
 ******************************************************************
 */

#ifndef FSMTEST_H
#define FSMTEST_H

// forward declaration because C++ is dumb
class FSM;
enum class FSMStates;

#include "src/FSM.h"

/**
 * Runnable is a function with no arguments returning nothing
 */
using Runnable = void (void);

class FSMTest {
public:
    static bool runTest(Runnable test, const FSM *fsm, const FSMStates& finalState);

};

#endif /* FSMTEST_H */
