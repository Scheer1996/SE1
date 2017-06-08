/** ****************************************************************
 * @file    DebugProcessImage.h 
 ******************************************************************
 */

#ifndef DEBUGPROCESSIMAGE_H
#define DEBUGPROCESSIMAGE_H

#include "FestoProcessImage.h"

/**
 * Debug implementation to simulate hardware.
 *
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    27.05.2017
 */
class DebugProcessImage: public FestoProcessImage {
private:
    unsigned short processImage;
    unsigned short processImageChange;
    unsigned short outputImage;
    unsigned short heightAnalogueValue;

    //setting inputs for test
    unsigned short processImageNew;
    unsigned short heightSensorNew;

    // fancy printing
    unsigned short previousInput;
    unsigned short previousOutput;
    unsigned short previousHeight;

// implement FestoProcessImage
public:
    DebugProcessImage();
    virtual ~DebugProcessImage() = default;

    virtual void updateProcessImage() override;
    virtual void applyOutputToProcess() override;
    virtual unsigned char isBitSet(unsigned short bitMask) override;
    virtual unsigned char isBitPosEdge(unsigned short bitMask) override;
    virtual unsigned char isBitNegEdge(unsigned short bitMask) override;
    virtual void setBitInOutput(unsigned short bitMask) override;
    virtual void clearBitInOutput(unsigned short bitMask) override;
    virtual unsigned short height() override;
    virtual void resetOutputs() override;

// setting inputs for test
private:
    void setBit(unsigned short& bitset, const unsigned short& mask);
    void clearBit(unsigned short& bitset, const unsigned short& mask);
    void conditionalSet(unsigned short& bitset, const unsigned short& mask, bool set);
public:
    void setItemAtBeginning(bool isThere);
    void setItemAtHeightSensor(bool isThere);
    void setItemAtMetalDetection(bool isThere);
    void setItemAtEnd(bool isThere);

    void setButtonStart(bool pressed);
    void setEmergencyStop(bool pressed);

    void setHeight(unsigned short newHeight);

// fancy printing
private:
    bool isBitSet(const unsigned short& bitset, const unsigned short& mask);
    void printFancy();
    void printInputFancy();
    void printOutputFancy();

};

#endif /* DEBUGPROCESSIMAGE_H_ */
