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
#include "minilab1008processimage.h"

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
    process_image = 0;
    process_image_old = 0;
    process_image_change = 0;
    output_image = 0;
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
    process_image_old = process_image; // save old values

    /* read input signals */
    process_image = 0;

#ifndef SIL
    unsigned short ioValue = 0;
    cbDIn(0, FIRSTPORTB, &ioValue);
    process_image = ioValue;
    cbDIn(0, FIRSTPORTCH, &ioValue); // High nibble already moved to low nibble
    process_image |= (ioValue & 0x0F) << 8;

    int error = 0;
    error = cbAIn(0, 0, BIP10VOLTS, &height_analogue_value);

#endif
    process_image_change = process_image_old ^ process_image;
}

void FestoMiniLab1008ProcessImage::applyOutputToProcess(void) {
#ifdef SIL
    printf("new output: %0x\n", output_image);
#else
    unsigned short ioValue = 0;
    ioValue = (output_image & 0xFF);
    cbDOut(0, FIRSTPORTA, ioValue);
    ioValue = ((output_image >> 8) & 0x0F);
    cbDOut(0, FIRSTPORTCL, ioValue);
#endif
}

unsigned char FestoMiniLab1008ProcessImage::isBitSet(unsigned short bitMask) {
    return ((process_image & bitMask) != 0);
}

unsigned char FestoMiniLab1008ProcessImage::isBitPosEdge(unsigned short bitMask) {
    return ((process_image & bitMask) == bitMask )&& ((process_image_change & bitMask) == bitMask);
}

unsigned char FestoMiniLab1008ProcessImage::isBitNegEdge(unsigned short bitMask) {
    return ((process_image & bitMask) == 0)&& ((process_image_change & bitMask) == bitMask);
}

void FestoMiniLab1008ProcessImage::setBitInOutput(unsigned short bitMask) {
    output_image |= bitMask;
}

void FestoMiniLab1008ProcessImage::clearBitInOutput(unsigned short bitMask) {
    output_image &= ~bitMask;
}

unsigned short FestoMiniLab1008ProcessImage::hight(){
    return height_analogue_value;
}

void FestoMiniLab1008ProcessImage::resetOutputs(void) {
    output_image = 0;
    applyOutputToProcess();
}




