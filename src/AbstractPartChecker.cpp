/** ****************************************************************
 * @file    AbstractPartChecker.cpp 
 ******************************************************************
 */

#include "AbstractPartChecker.h"

#include <cmath>

/**
 * threshold for considering two measurements as different.
 *
 * meant to counteract noise.
 */
static constexpr int ALLOWED_HEIGHT_DEVIATION = 10;

/**
 * height measurement of the belt (with no part on it)
 */
static constexpr int BELT_HEIGHT = 0;

/**
 * Constructs an AbstractPartChecker
 *
 * @param sensors
 */
AbstractPartChecker::AbstractPartChecker(FestoProcessSensors* sensors) :
        currentPart(nullptr), sensors(sensors), state(PartCheckerState::IDLE), lastHeight(
                0) {
}

AbstractPartChecker::~AbstractPartChecker() {
    if (currentPart) {
        delete currentPart;
    }
}

void AbstractPartChecker::evalCycle() {
    switch (state) {
        case PartCheckerState::IDLE:
            if (std::abs(sensors->getHeight() - BELT_HEIGHT)
                    > ALLOWED_HEIGHT_DEVIATION) {
                state = PartCheckerState::START_MEASURE;
            }
            break;
        case PartCheckerState::START_MEASURE:
            if (currentPart) {
                delete currentPart;
            }
            currentPart = new Part();
            lastHeight = sensors->getHeight();
            currentPart->addMeasurement( { lastHeight });
            state = PartCheckerState::MEASURE;
            break;
        case PartCheckerState::MEASURE: { // these need to be here, because of
                                          // the local variable currentHeight
            int currentHeight = sensors->getHeight();
            if (std::abs(currentHeight - lastHeight)
                    > ALLOWED_HEIGHT_DEVIATION) {
                currentPart->addMeasurement( { currentHeight });

            }
            if (std::abs(currentHeight - BELT_HEIGHT)
                    <= ALLOWED_HEIGHT_DEVIATION) {
                state = PartCheckerState::END_MEASURE;

            }
            lastHeight = currentHeight;
            break;
        }
        case PartCheckerState::END_MEASURE:
            if (!currentPart) {
                state = PartCheckerState::IDLE;
            }
            break;
    }
}

bool AbstractPartChecker::result() {
    if (currentPart && state == PartCheckerState::END_MEASURE) {
        // check if the part is valid
        bool result = checkPart(currentPart);

        // delete the part
        delete currentPart;
        currentPart = nullptr;

        return result;
    }
    //TODO: potentially throw an exception?
    return false;
}
