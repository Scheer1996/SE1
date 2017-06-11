/** ****************************************************************
 * @file    AbstractPartChecker.h 
 ******************************************************************
 */

#ifndef ABSTRACTPARTCHECKER_H
#define ABSTRACTPARTCHECKER_H

#include "Plugin.h"
#include "Part.h"
#include "FestoProcessSensors.h"

enum class PartCheckerState {IDLE, MEASURE, END_MEASURE};

/**
 * Abstract base class for evaluating height measurements
 *
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    25.05.2017
 */
class AbstractPartChecker : public Plugin {
private:
    Part *currentPart; ///< the Part that is currently being measured
    FestoProcessSensors *sensors; ///< for accessing height sensor
    PartCheckerState state; ///< internal FSM state
    int lastHeight; ///< for detecting when height has changed
public:
    AbstractPartChecker(FestoProcessSensors *sensors);
    virtual ~AbstractPartChecker();

    virtual void evalCycle() override;
    virtual bool result() override;

protected:
    /**
     * Check if a part is valid.
     *
     * to be implemented by subclasses to hook into the system
     *
     * @param part the part to check
     * @return true if the part is valid
     */
    virtual bool checkPart(const Part *part) = 0;
};

#endif /* ABSTRACTPARTCHECKER_H */
