/* 
 * File:   main.cpp
 * Author: Lehmann
 *
 * Created on 8. November 2013, 16:24
 */

#include <iostream>
#include <cmath>
#include "FSMFactory.h"

#include "LegoPartChecker.h"
#include "FestoMiniLab1008ProcessImage.h"

using namespace std;

/**
 * threshold for considering two measurements as different.
 *
 * meant to counteract noise.
 */
static constexpr int ALLOWED_HEIGHT_DEVIATION = 29;

/**
 * height measurement of the belt (with no part on it)
 */
static constexpr int BELT_HEIGHT = 3780;

/*
 * 
 */
int main(int argc, char** argv) {
#if 1
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
	FestoProcessAccess *fpa = new FestoProcessAccess(new FestoMiniLab1008ProcessImage());
    LegoPartChecker lpc(fpa);
    
    fpa->driveSlowRight();
    fpa->applyOutput();
    
    bool measure = false;
    
    while(1){
		fpa->updateInputs();
		lpc.evalCycle();
		//std::cout << fpa->getHeight() << std::endl;
		if(std::abs(fpa->getHeight() - BELT_HEIGHT) > ALLOWED_HEIGHT_DEVIATION){
			measure = true;
		} else if(measure){
			lpc.result();
			measure = false;
		}
	}
#endif
    return 0;
}

