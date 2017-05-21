/* 
 * File:   main.cpp
 * Author: Lehmann
 *
 * Created on 8. November 2013, 16:24
 */

#include <iostream>
#include "FSMFactory.h"

#include "Measurement.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
#if 0
    bool run = true; // set this variable to false whilst debugging to end program.
    FSMFactory factory;

    FSM* fsm = factory.createFSM();

    // Start Processing
    while (!fsm && run) {
        fsm->eval();
    }

    delete fsm;
#elif 1
    Measurement m(100);
    std::cout << m << std::endl;
#endif
    return 0;
}

