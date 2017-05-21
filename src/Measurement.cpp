/** ****************************************************************
 * @file    Measurement.cpp 
 ******************************************************************
 */

#include "Measurement.h"
#include <ctime> // for std::time_t
#include <iomanip> // for put_time

/**
 * Construct a Measurement from height with current timestamp.
 *
 * @param measurement the height
 */
Measurement::Measurement(int measurement) :
        measurement(measurement), timestamp(std::chrono::system_clock::now()) {
}

/**
 * Construct a measurement from height and timestamp
 *
 * @param measurement the height
 * @param timestamp   the Timestamp
 */
Measurement::Measurement(int measurement, Timestamp timestamp) :
        measurement(measurement), timestamp(timestamp) {
}

/**
 * Get the measured height
 *
 * @return the height
 */
int Measurement::getMeasurement() const {
    return measurement;
}

/**
 * Get the timestamp from when the measurement was taken
 *
 * @return the Timestamp
 */
Timestamp Measurement::getTimestamp() const {
    return timestamp;
}

/**
 * Print a Measurement to an ostream
 *
 * @param os the ostream to print to
 * @param m  the Measurement to print
 * @return os
 */
std::ostream& operator <<(std::ostream& os, const Measurement& m) {
    // get time as std::time_t for printing
    std::time_t tm = std::chrono::system_clock::to_time_t(m.getTimestamp());

    // print
    os << "Measurement: " << m.getMeasurement() << " at "
            << std::put_time(std::localtime(&tm), "%H:%M:%S");

    return os;
}

/**
 * Print a Measurement* to an ostream
 *
 * @param os the ostream to print to
 * @param m  the Measurement* to print
 * @return os
 */
std::ostream& operator <<(std::ostream& os, const Measurement* m) {
    return os << *m;
}
