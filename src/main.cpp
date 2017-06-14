/**
 * @file main.cpp
 *
 * program entry point.
 *
 * \author  Prof. Dr. Thomas Lehmann
 * @author Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 *
 * \version 1
 * \date    2013-11-08
 * @date    modified: 14.06.2017
 */
#include "FSMFactory.h"


int main(int argc, char** argv) {
    bool run = true; // set this variable to false whilst debugging to end program.
    FSMFactory factory;

    FSM* fsm = factory.createFSM();

    // Start Processing
    while (fsm && run) {
        fsm->eval();
    }

    delete fsm;
    return 0;
}

