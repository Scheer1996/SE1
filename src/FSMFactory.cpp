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

#include "FestoMiniLab1008ProcessImage.h"

FSM* FSMFactory::createFSM(){
       // Create Objects
    FestoProcessImage* processImage = new FestoMiniLab1008ProcessImage();
    FestoProcessAccess* processAccess = new FestoProcessAccess(processImage);
    //Plugin* plugin = new ...
    FSM* fsm = new FSM(processAccess, NULL);
    return fsm;
}
