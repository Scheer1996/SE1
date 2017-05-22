/** ****************************************************************
 * @file    Part.cpp 
 ******************************************************************
 */

#include "Part.h"

#include <ctime>
#include <iomanip>
#include <exception>

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
 * Is there anything stored in this part?
 *
 * @retval true  if Part contains at least one Measurement
 * @retval false if Part has no Measurements.
 */
bool Part::hasMeasurements() const {
    return !measurements.empty();
}

/**
 * Get the offset in ms a Measurement has from the beginning of this Part.
 *
 * Meant to be used with measurements in this Part.
 *
 * @param m the Measurement to calculate the offset for
 * @return the offset in ms
 *
 * @throws std::runtime_error if Part has no Measurement and therefore can't
 *         calculate an offset
 */
int Part::getOffsetInMS(const Measurement& m) const {
    if(!hasMeasurements()){
        throw std::runtime_error("No measurement to compare to!");
    }

    using namespace std::chrono;
    return duration_cast < milliseconds
            > (m.getTimestamp() - measurements.front().getTimestamp()).count();
}

/**
 * Print a Part to an ostream
 *
 * @param os the ostream to print to
 * @param p  the Part to print
 * @return os
 */
std::ostream& operator <<(std::ostream& os, const Part& p) {
    os << "Part: ";
    if (!p.hasMeasurements()) {
        os << "no measurements.";
    } else {
        auto tsFirst = p.getMeasurements().front().getTimestamp();

        // print timestamp of when the part was measured
        using namespace std::chrono;
        std::time_t tm = system_clock::to_time_t(tsFirst);
        os << std::put_time(std::localtime(&tm), "%H:%M:%S");

        for (auto&& m : p.getMeasurements()) {
            // calculate offset from first in ms
            int offset = p.getOffsetInMS(m);

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
