/** 
 * File:   minilab1008.h
 *
 * Class reads out the sensor values and controls actuators of the FESTO system 
 * via the MiniLab 1008 USB interface. 
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-01
 */

#ifndef MINILAB1008PROCESSIMAGE_H
#define	MINILAB1008PROCESSIMAGE_H

#include "FestoProcessImage.h"
// if SIL is defined, no hardware interface is accessed or compiled in.
//#define SIL

class FestoMiniLab1008ProcessImage : public FestoProcessImage {
private:
    unsigned short processImage;
    unsigned short processImageOld;
    unsigned short processImageChange;
    unsigned short outputImage;
    unsigned short heightAnalogueValue;
public:
    FestoMiniLab1008ProcessImage();
    virtual ~FestoMiniLab1008ProcessImage();
public:
    virtual void updateProcessImage(void);
    virtual void applyOutputToProcess(void);
    virtual unsigned char isBitSet(unsigned short bitMask);
    virtual unsigned char isBitPosEdge(unsigned short bitMask);
    virtual unsigned char isBitNegEdge(unsigned short bitMask);
    virtual void setBitInOutput(unsigned short bitMask);
    virtual void clearBitInOutput(unsigned short bitMask);
    virtual void resetOutputs(void);
    virtual unsigned short height();
private:
    void initProcessImageLayer(void);
};

#endif	/* PROCESSIMAGE_H */

