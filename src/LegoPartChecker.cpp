/** ****************************************************************
 * @file    LegoPartChecker.cpp 
 ******************************************************************
 */

#include <cmath>
#include "LegoPartChecker.h"

/**
 * should debug information be printed?
 */
#define PRINT_DEBUG true

#if PRINT_DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif

using namespace std::chrono;

/**
 * current time as reference starting time for the part
 */
static const auto ts = system_clock::now();

/*
 * @see LegoPartChecker::REFERENCE_PART
 */
const Part LegoPartChecker::REFERENCE_PART = { { 3414, ts }, { 3720, ts + milliseconds(432) }, {
        3418, ts + milliseconds(888) }, { 3114, ts + milliseconds(1368) }, { 3780, ts + milliseconds(1824) } };

/**
 * Time jitter allowed to still accept the Part
 */
static constexpr int ALLOWED_DELTA_T = 100; //ms

/**
 * Height jitter allowed to still accept the Part
 */
static constexpr int ALLOWED_DELTA_H = 30; //height sensor units

/**
 * Constructs a LegoPartChecker.
 *
 * @param sensors pointer to the hardware (used in superclass)
 */
LegoPartChecker::LegoPartChecker(FestoProcessSensors* sensors) :
        AbstractPartChecker(sensors) {
}

/*
 * @see AbstracPartChecker::checkPart
 */
bool LegoPartChecker::checkPart(const Part* part) {
#if PRINT_DEBUG
    cout << "Comparing" << endl << part << endl << "to" << endl
            << REFERENCE_PART << endl;
#endif

    if (part->getMeasurements().size()
            != REFERENCE_PART.getMeasurements().size()) {
        return false;
    }
    for (auto p = part->getMeasurements().begin(), ref =
            REFERENCE_PART.getMeasurements().begin();
            p != part->getMeasurements().end(); p++, ref++) {
        // check if heights match
        if (std::abs(p->getValue() - ref->getValue()) > ALLOWED_DELTA_H) {
#if PRINT_DEBUG
            cout << "Rejected because of height mismatch!" << endl;
#endif
            return false;
        }

        // check if width (time offset) matches
        if (std::abs(
                part->getOffsetInMS(*p) - REFERENCE_PART.getOffsetInMS(*ref))
                > ALLOWED_DELTA_T) {
#if PRINT_DEBUG
            cout << "Rejected because of time mismatch!" << endl;
#endif
            return false;
        }

    }
#if PRINT_DEBUG
    cout << "Accepted" << endl;
#endif
    return true;
}
