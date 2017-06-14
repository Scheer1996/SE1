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

/**
 * Constructs a DebugProcessImage
 */
DebugProcessImage::DebugProcessImage() :
        processImage(0), processImageChange(0), outputImage(0), heightAnalogueValue(
                0), processImageNew(0), heightSensorNew(0), previousInput(0), previousOutput(
                0), previousHeight(0) {
}

/*
 * @see - FestoProcessImage::updateProcessImage()
 */
void DebugProcessImage::updateProcessImage() {
    processImageChange = processImage ^ processImageNew;
    processImage = processImageNew;
    heightAnalogueValue = heightSensorNew;
}

/*
 * @see - FestoProcessImage::applyOutputToProcess()
 */
void DebugProcessImage::applyOutputToProcess() {
    printFancy();
}

/*
 * @see - FestoProcessImage::isBitSet(unsigned short)
 */
unsigned char DebugProcessImage::isBitSet(unsigned short bitMask) {
    return isBitSet(processImage, bitMask);
}

/*
 * @see - FestoProcessImage::isBitPosEdge(unsigned short)
 */
unsigned char DebugProcessImage::isBitPosEdge(unsigned short bitMask) {
    return (processImageChange & processImage & bitMask) == bitMask;
}

/*
 * @see - FestoProcessImage::isBitNegEdge(unsigned short)
 */
unsigned char DebugProcessImage::isBitNegEdge(unsigned short bitMask) {
    return (processImageChange & ~processImage & bitMask) == bitMask;
}

/*
 * @see - FestoProcessImage::setBitInOutput(unsigned short)
 */
void DebugProcessImage::setBitInOutput(unsigned short bitMask) {
    setBit(outputImage, bitMask);
}

/*
 * @see - FestoProcessImage::clearBitInOutput(unsigned short)
 */
void DebugProcessImage::clearBitInOutput(unsigned short bitMask) {
    clearBit(outputImage, bitMask);
}

/*
 * @see - FestoProcessImage::height()
 */
unsigned short DebugProcessImage::height() {
    return heightAnalogueValue;
}

/*
 * @see - FestoProcessImage::resetOutputs()
 */
void DebugProcessImage::resetOutputs() {
    outputImage = 0;
    applyOutputToProcess();
}

/* ************************************************************
 * Setting Inputs for test
 * ********************************************************* */

/**
 * Set one or more bits to 1
 *
 * @param bitset set of bits to modify
 * @param mask   which of the bits in bitset should be modified
 */
void DebugProcessImage::setBit(unsigned short & bitset,
        const unsigned short & mask) {
    bitset |= mask;
}

/**
 * Set one or more bits to 0
 *
 * @param bitset set of bits to modify
 * @param mask   which of the bits in bitset should be modified
 */
void DebugProcessImage::clearBit(unsigned short & bitset,
        const unsigned short & mask) {
    bitset &= ~mask;
}

/**
 * Set bit(s) to 1 or 0, depending on he value of set
 *
 * @param bitset set of bits to modify
 * @param mask   which of the bits should be modified
 * @param set    true -> set to 1, false -> set to 0
 */
void DebugProcessImage::conditionalSet(unsigned short & bitset,
        const unsigned short & mask, bool set) {
    if (set) {
        setBit(bitset, mask);
    } else {
        clearBit(bitset, mask);
    }
}

/**
 * Control light barrier at the beginning of the belt
 *
 * @param isThere is it blocked by an item
 */
void DebugProcessImage::setItemAtBeginning(bool isThere) {
    // active low
    conditionalSet(processImageNew, ITEM_DETECTED, !isThere);
}

/**
 * Control light switch underneath the height sensor
 *
 * @param isThere is it blocked by an item
 */
void DebugProcessImage::setItemAtHeightSensor(bool isThere) {
    // active low
    conditionalSet(processImageNew, ITEM_AT_HIGHT_SENSOR, !isThere);
}

/**
 * Control light switch at slide/ underneath the metal detector
 *
 * @param isThere is it blocked by an item
 */
void DebugProcessImage::setItemAtMetalDetection(bool isThere) {
    // active low
    conditionalSet(processImageNew, ITEM_AT_JUNCTION, !isThere);
}

/**
 * Control light barrier at the end of the belt
 *
 * @param isThere is it blocked by an item
 */
void DebugProcessImage::setItemAtEnd(bool isThere) {
    // active low
    conditionalSet(processImageNew, ITEM_AT_END, !isThere);
}

/**
 * Control the start button
 *
 * @param pressed is the button pressed or not
 */
void DebugProcessImage::setButtonStart(bool pressed) {
    conditionalSet(processImageNew, BUTTON_START_PRESSED, pressed);
}

/**
 * Control the emergency stop button
 *
 * @param pressed is the button pressed or not
 */
void DebugProcessImage::setEmergencyStop(bool pressed) {
    // active low
    conditionalSet(processImageNew, EMERGENCY_STOP_PRESSED, !pressed);
}

/**
 * Control the height sensor.
 *
 * @param newHeight set height measurement
 */
void DebugProcessImage::setHeight(unsigned short newHeight) {
    heightSensorNew = newHeight;
}

/* ************************************************************
 * Fancy Printing
 * ********************************************************* */
/**
 * Check if bit(s) is (are) set.
 *
 * @param bitset set of bits to check
 * @param mask   which of the bits in bitset are supposed to be set?
 * @return       true, if all bits in mask are set
 */
bool DebugProcessImage::isBitSet(const unsigned short & bitset,
        const unsigned short & mask) {
    return (bitset & mask) == mask;
}

/**
 * Print the current hardware state in a "fancy" way.
 *
 * Only prints if something has changed. Will print height, input + output in
 * binary and input + output decoded as text.
 */
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

/**
 * Print input in a "fancy" way.
 *
 * Will print height and input as binary and decided as text.
 */
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

/**
 * Print output in a "fancy" way.
 *
 * Will print output in binary and decoded as text.
 */
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

    cout << "Junction: ";
    if(isBitSet(outputImage, JUNCTION_OPEN)){
        cout << "Open (Item can pass)";
    } else {
        cout << "Closed (Sending to slide)";
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
