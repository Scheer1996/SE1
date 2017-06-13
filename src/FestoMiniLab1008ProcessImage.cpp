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

#include <cstdio>

#include "FestoMiniLab1008ProcessImage.h"

using namespace std;

#ifndef SIL

#ifdef	__cplusplus
extern "C" {
#endif

#include "cbw.h"

#ifdef	__cplusplus
}
#endif

#endif

FestoMiniLab1008ProcessImage::FestoMiniLab1008ProcessImage() {
    processImage = 0;
    processImageOld = 0;
    processImageChange = 0;
    outputImage = 0;
    initProcessImageLayer();
    updateProcessImage();
}

FestoMiniLab1008ProcessImage::~FestoMiniLab1008ProcessImage() {
    resetOutputs();
}

void FestoMiniLab1008ProcessImage::initProcessImageLayer(void) {
    /* connect to board */
#ifndef SIL
    cbDConfigPort(0, FIRSTPORTA, DIGITALOUT);
    cbDConfigPort(0, FIRSTPORTB, DIGITALIN);
    cbDConfigPort(0, FIRSTPORTCH, DIGITALIN);
    cbDConfigPort(0, FIRSTPORTCL, DIGITALOUT);
#endif
}

void FestoMiniLab1008ProcessImage::updateProcessImage(void) {
    processImageOld = processImage; // save old values

    /* read input signals */
    processImage = 0;

#ifndef SIL
    unsigned short ioValue = 0;
    cbDIn(0, FIRSTPORTB, &ioValue);
    processImage = ioValue;
    cbDIn(0, FIRSTPORTCH, &ioValue); // High nibble already moved to low nibble
    processImage |= (ioValue & 0x0F) << 8;

    int error = 0;
    error = cbAIn(0, 0, BIP10VOLTS, &heightAnalogueValue);

#endif
    processImageChange = processImageOld ^ processImage;
}

void FestoMiniLab1008ProcessImage::applyOutputToProcess(void) {
#ifdef SIL
    printf("new output: %0x\n", outputImage);
#else
    unsigned short ioValue = 0;
    ioValue = (outputImage & 0xFF);
    cbDOut(0, FIRSTPORTA, ioValue);
    ioValue = ((outputImage >> 8) & 0x0F);
    cbDOut(0, FIRSTPORTCL, ioValue);
#endif
}

unsigned char FestoMiniLab1008ProcessImage::isBitSet(unsigned short bitMask) {
    return ((processImage & bitMask) != 0);
}

unsigned char FestoMiniLab1008ProcessImage::isBitPosEdge(unsigned short bitMask) {
    return ((processImage & bitMask) == bitMask )&& ((processImageChange & bitMask) == bitMask);
}

unsigned char FestoMiniLab1008ProcessImage::isBitNegEdge(unsigned short bitMask) {
    return ((processImage & bitMask) == 0)&& ((processImageChange & bitMask) == bitMask);
}

void FestoMiniLab1008ProcessImage::setBitInOutput(unsigned short bitMask) {
    outputImage |= bitMask;
}

void FestoMiniLab1008ProcessImage::clearBitInOutput(unsigned short bitMask) {
    outputImage &= ~bitMask;
}

unsigned short FestoMiniLab1008ProcessImage::height(){
    return heightAnalogueValue;
}

void FestoMiniLab1008ProcessImage::resetOutputs(void) {
    outputImage = 0;
    applyOutputToProcess();
}




