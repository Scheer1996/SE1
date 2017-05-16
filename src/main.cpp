/* 
 * File:   main.cpp
 * Author: Lehmann
 *
 * Created on 8. November 2013, 16:24
 */

#include <cstdlib>
#include <cstdio>

#include "factory.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    bool run = true; // set this variable to false whilst debugging to end program.
    FSMFactory factory;

    FSM* fsm = factory.createFSM();

    // Start Processing
    while (fsm != NULL && run) {
        fsm->eval();
    }

    delete fsm;

    return 0;
}

