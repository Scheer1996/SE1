/** ****************************************************************
 * @file    test/test_base.cpp
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    03.11.2016
 * @brief   Implementation for test base
 ******************************************************************
 */

#include "test_base.h"
#include <cmath>

/**
 * The maximum difference between to doubles to still count them as equal
 */
#define EPSILON 1e-5

using namespace std;

/*
 * Assertion for int
 */
bool assert_equals(std::string msg, int act, int exp, std::string file,
        int line) {
    if (act != exp) {
        cout << RED << "Failed! - " << msg << ": expected <" << exp
                << "> but was <" << act << "> - " << file << ":" << line
                << RESET << endl;
        return false;
    }
    return true;
}

/*
 * Assertion for double
 */
bool assert_equals(std::string msg, double act, double exp, std::string file,
        int line) {
    if (fabs(act - exp) > EPSILON) {
        cout << RED << "Failed! - " << msg << ": expected <" << exp
                << "> but was <" << act << "> - " << file << ":" << line
                << RESET << endl;
        return false;
    }
    return true;
}

/*
 * Assertion for correctness
 */
bool assert_true(std::string msg, bool res, std::string file, int line) {
    if (!res) {
        cout << RED << "Failed! - " << msg << " - " << file << ":" << line
                << RESET << endl;
        return false;
    }
    return true;
}

/*template<class T>
 bool assert_equals(std::string msg, T act, T exp) {
 if (act != exp) {
 cout << "Failed! - " << msg << ": expected <" << exp << "> but was <"
 << act << ">" << endl;
 return false;
 }
 return true;
 }*/

