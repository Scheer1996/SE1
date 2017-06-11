/** ****************************************************************
 * @file    LegoPartChecker.cpp 
 ******************************************************************
 */

#include "LegoPartChecker.h"

#define PRINT_DEBUG

#ifdef PRINT_DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif

using namespace std::chrono;
static const auto ts = system_clock::now();

const Part LegoPartChecker::REFERENCE_PART = { { 10, ts }, { 20, ts + 10ms }, {
        30, ts + 20ms }, { 10, ts + 35ms }, { 0, ts + 50ms } };

/**
 * Time jitter allowed to still accept the Part
 */
static constexpr int ALLOWED_DELTA_T = 10; //ms

/**
 * Height jitter allowed to still accept the Part
 */
static constexpr int ALLOWED_DELTA_H = 10; //height sensor units

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
#ifdef PRINT_DEBUG
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
#ifdef PRINT_DEBUG
            cout << "Rejected because of height mismatch!" << endl;
#endif
            return false;
        }

        // check if width (time offset) matches
        if (std::abs(
                part->getOffsetInMS(*p) - REFERENCE_PART.getOffsetInMS(*ref))
                > ALLOWED_DELTA_T) {
#ifdef PRINT_DEBUG
            cout << "Rejected because of time mismatch!" << endl;
#endif
            return false;
        }

    }
#ifdef PRINT_DEBUG
    cout << "Accepted" << endl;
#endif
    return true;
}
