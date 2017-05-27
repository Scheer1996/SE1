/** ****************************************************************
 * @file    main.cpp 
 ******************************************************************
 */

#include "test_base.h"

#include "measurement.test"
#include "legopartchecker.test"

int main() {
    INIT_MAIN
    // Measurement
    PERFORM_TEST(testMeasurement)

    // Lego Part checker
    PERFORM_TEST(testCheckPart);
    END_MAIN
}
