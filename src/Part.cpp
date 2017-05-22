/** ****************************************************************
 * @file    Part.cpp 
 ******************************************************************
 */

#include "Part.h"

#include <ctime>
#include <iomanip>

/**
 * Add a Measurement to the Part.
 *
 * @param m the Measurement to add
 */
void Part::addMeasurement(Measurement& m) {
    measurements.push_back(m);
}

/**
 * Move a Measurement to the Part.
 *
 * @param m the Measurement to add
 */
void Part::addMeasurement(Measurement&& m) {
    measurements.push_back(m);
}

/**
 * Get all the Measurements that make up this Part
 *
 * @return the Measurements
 */
const std::vector<Measurement>& Part::getMeasurements() const {
    return measurements;
}

/**
 * Print a Part to an ostream
 *
 * @param os the ostream to print to
 * @param p  the Part to print
 * @return os
 */
std::ostream& operator <<(std::ostream& os, const Part& p) {
    using namespace std::chrono;

    os << "Part: ";
    if (p.getMeasurements().empty()) {
        os << "no Measurements...";
    } else {
        auto tsFirst = p.getMeasurements().front().getTimestamp();

        // print timestamp of when the part was measured
        std::time_t tm = system_clock::to_time_t(tsFirst);
        os << std::put_time(std::localtime(&tm), "%H:%M:%S");

        for (auto&& m : p.getMeasurements()) {
            // calculate offset from first in ms
            auto offset = duration_cast < milliseconds
                    > (m.getTimestamp() - tsFirst).count();

            // print "value | offset"
            os << std::endl << std::setw(4) << m.getValue() << " | ";
            if (offset >= 0) {
                os << "+";
            }
            os << offset << " ms";
        }
    }

    return os;
}

/**
 * Print a Part* to an ostream
 *
 * @param os the ostream to print to
 * @param p  the Part* to print
 * @return os
 */
std::ostream& operator <<(std::ostream& os, const Part* p) {
    return os << *p;
}
