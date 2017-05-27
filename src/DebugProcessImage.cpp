/** ****************************************************************
 * @file    DebugProcessImage.cpp 
 ******************************************************************
 */

#include "DebugProcessImage.h"
#include <iostream>

template<typename T>
void printBinary(const T number, bool padWith0 = false);

using std::cout;
using std::endl;

DebugProcessImage::DebugProcessImage() :
        processImage(0), processImageOld(0), processImageChange(0), outputImage(
                0), heightAnalogueValue(0) {
}

// TODO: debug implementation
void DebugProcessImage::updateProcessImage() {
    cout << "Input:" << endl;
    printBinary(processImage, true);
    printBinary(processImageOld, true);
    printBinary(processImageChange, true);
    cout << endl;
}

// TODO: debug implementation
void DebugProcessImage::applyOutputToProcess() {
    cout << "Output: " << endl;
    printBinary(outputImage, true);
    cout << endl;
}

// TODO: debug implementation
unsigned char DebugProcessImage::isBitSet(unsigned short bitMask) {
    return 0;
}

// TODO: debug implementation
unsigned char DebugProcessImage::isBitPosEdge(unsigned short bitMask) {
    return 0;
}

// TODO: debug implementation
unsigned char DebugProcessImage::isBitNegEdge(unsigned short bitMask) {
    return 0;
}

/**
 * Sets one or more bits in the output
 *
 * @param bitMask which bits to set
 */
void DebugProcessImage::setBitInOutput(unsigned short bitMask) {
    outputImage |= bitMask;
}

/**
 * Clears one or more bits from the output
 *
 * @param bitMask which bits to clear
 */
void DebugProcessImage::clearBitInOutput(unsigned short bitMask) {
    outputImage &= ~bitMask;
}

/**
 * get the height sensor reading
 */
unsigned short DebugProcessImage::height() {
    return heightAnalogueValue;
}

/**
 * Reset all outputs to 0
 */
void DebugProcessImage::resetOutputs() {
    outputImage = 0;
    applyOutputToProcess();
}

/**
 * Print binary representation of the number
 *
 * @param number the number to print
 * @param padWith0 should the number be padded? example:
 *                 12 in 8bit - padded: 00001100 - unpadded: 1100
 */
template<typename T>
void printBinary(const T number, bool padWith0) {
    bool thereWasAOne = false;
    for (int i = sizeof(T) * 8 - 1; i >= 0; i--) {
        if (number & (1 << i)) {
            thereWasAOne = true;
            cout << "1";
        } else if (thereWasAOne || padWith0) {
            cout << "0";
        }
    }
    cout << endl;
}
