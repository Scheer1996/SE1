/** ****************************************************************
 * @file    DebugProcessImage.cpp 
 ******************************************************************
 */

#include "DebugProcessImage.h"
#include "iomasks.h"
#include <iostream>

template<typename T>
static void printBinary(const T number, bool padWith0 = false);

using std::cout;
using std::endl;

DebugProcessImage::DebugProcessImage() :
        processImage(0), processImageChange(0), outputImage(0), heightAnalogueValue(
                0), processImageNew(0), heightSensorNew(0), previousInput(0), previousOutput(
                0), previousHeight(0) {
}

void DebugProcessImage::updateProcessImage() {
    processImageChange = processImage ^ processImageNew;
    processImage = processImageNew;
    heightAnalogueValue = heightSensorNew;

    printFancy();
}

void DebugProcessImage::applyOutputToProcess() {
    printFancy();
}

unsigned char DebugProcessImage::isBitSet(unsigned short bitMask) {
    return isBitSet(processImage, bitMask);
}

unsigned char DebugProcessImage::isBitPosEdge(unsigned short bitMask) {
    return (processImageChange & processImage & bitMask) == bitMask;
}

unsigned char DebugProcessImage::isBitNegEdge(unsigned short bitMask) {
    return (processImageChange & ~processImage & bitMask) == bitMask;
}

/**
 * Sets one or more bits in the output
 *
 * @param bitMask which bits to set
 */
void DebugProcessImage::setBitInOutput(unsigned short bitMask) {
    setBit(outputImage, bitMask);
}

/**
 * Clears one or more bits from the output
 *
 * @param bitMask which bits to clear
 */
void DebugProcessImage::clearBitInOutput(unsigned short bitMask) {
    clearBit(outputImage, bitMask);
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

/* ************************************************************
 * Setting Inputs for test
 * ********************************************************* */

void DebugProcessImage::setBit(unsigned short & bitset,
        const unsigned short & mask) {
    bitset |= mask;
}

void DebugProcessImage::clearBit(unsigned short & bitset,
        const unsigned short & mask) {
    bitset &= ~mask;
}

void DebugProcessImage::conditionalSet(unsigned short & bitset,
        const unsigned short & mask, bool set) {
    if (set) {
        setBit(bitset, mask);
    } else {
        clearBit(bitset, mask);
    }
}

void DebugProcessImage::setItemAtBeginning(bool isThere) {
    // active low
    conditionalSet(processImageNew, ITEM_DETECTED, !isThere);
}

void DebugProcessImage::setItemAtHeightSensor(bool isThere) {
    // active low
    conditionalSet(processImageNew, ITEM_AT_HIGHT_SENSOR, !isThere);
}

void DebugProcessImage::setItemAtMetalDetection(bool isThere) {
    // active low
    conditionalSet(processImageNew, ITEM_AT_JUNCTION, !isThere);
}

void DebugProcessImage::setItemAtEnd(bool isThere) {
    // active low
    conditionalSet(processImageNew, ITEM_AT_END, !isThere);
}

void DebugProcessImage::setButtonStart(bool pressed) {
    conditionalSet(processImageNew, BUTTON_START_PRESSED, pressed);
}

void DebugProcessImage::setEmergencyStop(bool pressed) {
    // active low
    conditionalSet(processImageNew, EMERGENCY_STOP_PRESSED, !pressed);
}

void DebugProcessImage::setHeight(unsigned short newHeight) {
    heightSensorNew = newHeight;
}

/* ************************************************************
 * Fancy Printing
 * ********************************************************* */

bool DebugProcessImage::isBitSet(const unsigned short & bitset,
        const unsigned short & mask) {
    return (bitset & mask) == mask;
}

void DebugProcessImage::printFancy() {
    if (processImage == previousInput && outputImage == previousOutput
            && previousHeight == heightAnalogueValue) {
        return;
    }

    cout << "========================================" << endl;
    printInputFancy();
    cout << endl;
    printOutputFancy();

    previousInput = processImage;
    previousOutput = outputImage;
    previousHeight = heightAnalogueValue;
}

void DebugProcessImage::printInputFancy() {
    cout << "Height: " << heightAnalogueValue << endl;
    cout << "Input: ";
    printBinary(processImage, true);
    cout << endl;

    if (!isBitSet(processImage, ITEM_DETECTED)) {
        cout << "Item at the beginning" << endl;
    }
    if (!isBitSet(processImage, ITEM_AT_HIGHT_SENSOR)) {
        cout << "Item at the height sensor" << endl;
    }
    if (!isBitSet(processImage, ITEM_AT_JUNCTION)) {
        cout << "Item at the metal detector" << endl;
    }
    if (!isBitSet(processImage, ITEM_AT_END)) {
        cout << "Item at the end" << endl;
    }

    if (isBitSet(processImage, BUTTON_START_PRESSED)) {
        cout << "Start Button pressed" << endl;
    }
    if (!isBitSet(processImage, EMERGENCY_STOP_PRESSED)) {
        cout << "EMERGENCY STOP!!" << endl;
    }
}

void DebugProcessImage::printOutputFancy() {
    cout << "Output: ";
    printBinary(outputImage, true);
    cout << endl;

    cout << "Belt: ";
    if (isBitSet(outputImage, DRIVE_STOP)) {
        cout << "Stopped";
    } else {
        if (isBitSet(outputImage, DRIVE_DIRECTION_RIGHT)) {
            cout << "Right";
            if (isBitSet(outputImage, DRIVE_SLOW)) {
                cout << " Slow";
            }
        } else if (isBitSet(outputImage, DRIVE_DIRECTION_LEFT)) {
            cout << "Left";
            if (isBitSet(outputImage, DRIVE_SLOW)) {
                cout << " Slow";
            }
        } else {
            cout << "Stopped";
        }
    }
    cout << endl;

    cout << "Lights: ";
    std::string delim = "";
    if (isBitSet(outputImage, TRAFIC_LIGHT_RED)) {
        cout << "Red";
        delim = " and ";
    }
    if (isBitSet(outputImage, TRAFIC_LIGHT_YELLOW)) {
        cout << "Yellow";
        delim = " and ";
    }
    if (isBitSet(outputImage, TRAFIC_LIGHT_GREEN)) {
        cout << delim << "Green";
        delim = " and ";
    }
    if (delim == "") {
        cout << "Off";
    }
    cout << endl;

    if (isBitSet(outputImage, LED_START_BUTTON)) {
        cout << "Start Button LED on" << endl;
    }
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
}
