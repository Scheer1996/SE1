/** ****************************************************************
 * @file    FSMTest.cpp 
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    08.06.2017
 ******************************************************************
 */

#include "FSMTest.h"

/**
 * Runs a test on an FSM and returns if the final state is correct.
 *
 * @param test       the test to run
 * @param fsm        the FSM to run it on
 * @param finalState the final state that the FSM should be in
 *
 * @return true, if specified final state matches state of fsm after the test
 */
bool FSMTest::runTest(Runnable test, const FSM* fsm,
        const FSMStates& finalState) {
    test();
    return fsm->currentState == finalState;
}
