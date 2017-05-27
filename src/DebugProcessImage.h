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
    unsigned short processImageOld;
    unsigned short processImageChange;
    unsigned short outputImage;
    unsigned short heightAnalogueValue;
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
};

#endif /* DEBUGPROCESSIMAGE_H_ */
