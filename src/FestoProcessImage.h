/** ****************************************************************
 * @file    FestoProcessImage.h
 ******************************************************************
 */

#ifndef PROCESSIMAGE_H
#define	PROCESSIMAGE_H

/**
 * Interface definition for low level access to sensors and actuators of the
 * FESTO system.
 *
 * @author Prof. Dr. Thomas Lehmann
 * @author Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date   01.11.2013
 * @date   modified: 11.06.2017
 */
class FestoProcessImage {
public:
    /**
     * Read input from the machine.
     */
    virtual void updateProcessImage() = 0;

    /**
     * Send output buffer to the machine.
     */
    virtual void applyOutputToProcess() = 0;

    /**
     * Check if bits from mask are set in input buffer.
     *
     * @param bitMask the bitmask to check
     * @return true, if all bits are set
     */
    virtual unsigned char isBitSet(unsigned short bitMask) = 0;

    /**
     * Check if bits from mask have changed and are set in input buffer.
     *
     * @param bitMask the bitmask to check
     * @return true, if all bits have changed are set
     */
    virtual unsigned char isBitPosEdge(unsigned short bitMask) = 0;

    /**
     * Check if bits from mask have changed and are unset in input buffer.
     *
     * @param bitMask the bitmask to check
     * @return true, if all bits have changed are unset
     */
    virtual unsigned char isBitNegEdge(unsigned short bitMask) = 0;

    /**
     * Set bits from mask to 1 in output buffer.
     *
     * @param bitMask bits to set
     */
    virtual void setBitInOutput(unsigned short bitMask) = 0;

    /**
     * Set bits from mask to 0 in output buffer.
     *
     * @param bitMask bits to clear
     */
    virtual void clearBitInOutput(unsigned short bitMask) = 0;

    /**
     * Read height from height sensor.
     *
     * @return the height value in some unit
     */
    virtual unsigned short height() = 0;

    /**
     * Set output buffer to 0 and apply it to the machine.
     */
    virtual void resetOutputs() = 0;

    /**
     * Default virtual destructor
     */
    virtual ~FestoProcessImage() = default;
};

#endif	/* PROCESSIMAGE_H */

