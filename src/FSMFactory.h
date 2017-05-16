/** 
 * File:   factory.h
 *
 * Service class setting up all objects of the system.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-10
 */

#ifndef FACTORY_H
#define	FACTORY_H

#include "FSM.h"

class FSMFactory{
public:
    FSM* createFSM();
};

#endif	/* FACTORY_H */

