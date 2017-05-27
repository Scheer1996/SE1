/* 
 * File:   main.cpp
 * Author: Lehmann
 *
 * Created on 8. November 2013, 16:24
 */

#include <iostream>
#include "FSMFactory.h"

#include "Part.h"

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
    while (fsm && run) {
        fsm->eval();
    }

    delete fsm;
    fsm = nullptr;
#elif 1
    Measurement m(100);
    std::cout << m << std::endl;

    Part p;
    std::cout << p << std::endl;

    p.addMeasurement(m);
    std::cout << p << std::endl;

    using namespace std::chrono;
    p.addMeasurement({10, system_clock::now() + 300ms});
    std::cout << p << std::endl;

    Timestamp ts = system_clock::now();
    Part p2 = {{10, ts}, {20, ts + 10ms}, {30, ts + 20ms}};
    std::cout << p2 << std::endl;
#endif
    return 0;
}

