/** ****************************************************************
 * @file    main.cpp 
 ******************************************************************
 */

#include "test_base.h"

#include "measurement.test"

int main() {
    INIT_MAIN
    // Measurement
    PERFORM_TEST(testMeasurement)
    END_MAIN
}
