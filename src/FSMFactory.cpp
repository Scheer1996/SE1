/** 
 * @file FSMFactory.cpp
 *
 * Service class setting up all objects of the system.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * @author Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 *
 * \version 1
 * \date    2013-11-10
 * @date    modified: 14.06.2017
 */

#include "FestoProcessAccess.h"
#include "FSMFactory.h"
#include "LegoPartChecker.h"

#ifndef SIL
#include "FestoMiniLab1008ProcessImage.h"
#else
#include "DebugProcessImage.h"
#endif

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
