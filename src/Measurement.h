/** ****************************************************************
 * @file    Measurement.h 
 ******************************************************************
 */

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <chrono>
#include <string>
#include <iostream>

using Timestamp = std::chrono::system_clock::time_point;

/**
 * Storage class for a measurement.
 *
 * Provides the measurement and the associated timestamp
 *
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    21.05.2017
 */
class Measurement {
private:
    int value;           ///< the value of the measurement that was taken
    Timestamp timestamp; ///< the Timestamp of when the measurement was taken
public:
    Measurement(int measurement);
    Measurement(int measurement, Timestamp timestamp);

    int getValue() const;
    Timestamp getTimestamp() const;
};

std::ostream& operator<<(std::ostream& os, const Measurement& m);
std::ostream& operator<<(std::ostream& os, const Measurement* m);

#endif /* MEASUREMENT_H */
