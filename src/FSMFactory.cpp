/** 
 * File:   factory.cpp
 *
 * Service class setting up all objects of the system.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-10
 */

#include "FestoProcessAccess.h"
#include "FSMFactory.h"
#include "LegoPartChecker.h"

#include "FestoMiniLab1008ProcessImage.h"
#include "DebugProcessImage.h"

FSM* FSMFactory::createFSM(){
       // Create Objects
    FestoProcessImage* processImage;
#ifndef SIL
    processImage = new FestoMiniLab1008ProcessImage();
#else
    processImage = new DebugProcessImage();
#endif
    FestoProcessAccess* processAccess = new FestoProcessAccess(processImage);
    Plugin* plugin = new LegoPartChecker(processAccess);
    FSM* fsm = new FSM(processAccess, plugin);
    return fsm;
}
