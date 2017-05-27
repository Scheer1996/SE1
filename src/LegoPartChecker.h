/** ****************************************************************
 * @file    LegoPartChecker.h 
 ******************************************************************
 */

#ifndef LEGOPARTCHECKER_H
#define LEGOPARTCHECKER_H

#include "AbstractPartChecker.h"

/**
 * AbstractPartChecker specialization for a Lego Part.
 *
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    27.05.2017
 */
class LegoPartChecker: public AbstractPartChecker {
private:
    /**
     * Reference Part to compare to
     */
    static const Part REFERENCE_PART;
public:
    LegoPartChecker(FestoProcessSensors *sensors);
    virtual ~LegoPartChecker() = default;

    virtual bool checkPart(const Part *part) override;
};

#endif /* LEGOPARTCHECKER_H */
