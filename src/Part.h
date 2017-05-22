/** ****************************************************************
 * @file    Part.h 
 ******************************************************************
 */

#ifndef PART_H
#define PART_H

#include <vector>
#include "Measurement.h"

/**
 * Storage class for a Part.
 *
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    22.05.2017
 */
class Part {
private:
    std::vector<Measurement> measurements; ///< container for the Measurements
public:
    void addMeasurement(Measurement& m);
    void addMeasurement(Measurement&& m);
    const std::vector<Measurement>& getMeasurements() const;

    bool hasMeasurements() const;
    int getOffsetInMS(const Measurement& m) const;
};

std::ostream& operator<<(std::ostream& os, const Part& m);
std::ostream& operator<<(std::ostream& os, const Part* m);

#endif /* PART_H */
