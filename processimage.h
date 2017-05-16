/** 
 * File:   processimage.h
 * Author: Prof. Dr. Thomas Lehmann
 *
 * Interface definition for low level access to sensors and actuators of the 
 * FESTO system.
 * 
 * Created on 1. November 2013, 11:50
 */

#ifndef PROCESSIMAGE_H
#define	PROCESSIMAGE_H

class FestoProcessImage {
public:
    virtual void updateProcessImage(void)=0;
    virtual void applyOutputToProcess(void)=0;
    virtual unsigned char isBitSet(unsigned short bitMask)=0;
    virtual unsigned char isBitPosEdge(unsigned short bitMask)=0;
    virtual unsigned char isBitNegEdge(unsigned short bitMask)=0;
    virtual void setBitInOutput(unsigned short bitMask)=0;
    virtual void clearBitInOutput(unsigned short bitMask)=0;
    virtual unsigned short hight()=0;
    virtual void resetOutputs(void)=0;
};

#endif	/* PROCESSIMAGE_H */

