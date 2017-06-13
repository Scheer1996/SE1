/** ****************************************************************
 * @file    FSMTest.cpp 
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    08.06.2017
 * @brief   <A brief description>
 ******************************************************************
 */

#include "FSMTest.h"

bool FSMTest::runTest(Runnable test, const FSM* fsm,
        const FSMStates& finalState) {
    test();
    return fsm->currentState == finalState;
}
