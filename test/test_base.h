/** ****************************************************************
 * @file    test/test_base.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @version 1.0
 * @date    03.11.2016
 * @brief   Base Header for tests
 ******************************************************************
 */

#ifndef TEST_BASE_H_
#define TEST_BASE_H_

#include <iostream>

//Colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define GRAY "\033[90m"

/**
 * @brief Starts a test method
 */
#define INIT_TEST std::cout << __FUNCTION__ << ": " << std::flush;

/**
 * @brief Ends a test method
 */
#define END_TEST std::cout << GREEN << "Passed" << RESET << std::endl; return true;

/**
 * @brief Manually fails a test
 */
#define FAIL(msg) std::cout << RED << "Failed - " << (msg) << " - " \
        << __FILE__ << ":" << __LINE__ << RESET << std::endl; return false;

/**
 * @brief Manually passes a test
 */
#define PASS std::cout << GREEN << "Passed" << GRAY << " (Test author manually forced test to pass!)" << RESET << std::endl; return true;

/**
 * @brief Performs an Assertion for equality
 *
 * refer to assert_equals for parameters
 */
#define ASSERT_EQUALS(msg, act, exp) if(!assert_equals((msg), (act), (exp), __FILE__, __LINE__)) { return false; };

/**
 * @brief Performs an Assertion for correctness
 *
 * refer to assert_true for parameters
 */
#define ASSERT_TRUE(msg, res) if(!assert_true((msg), (res), __FILE__, __LINE__)) { return false; };

/**
 * @brief Performs an Assertion for falseness
 *
 * refer to assert_true for parameters
 */
#define ASSERT_FALSE(msg, res)  if(!assert_true((msg), !(res), __FILE__, __LINE__)) { return false; };

/**
 * @brief Initializes the main method that performs all the tests
 */
#define INIT_MAIN int success_counter = 0; int failed_counter = 0;

/**
 * @brief Runs a test
 */
#define PERFORM_TEST(x) if(x()){ success_counter++; } else { failed_counter++; }

/**
 * @brief Ends the main method and prints information
 */
#define END_MAIN std::cout << "==================================" << std::endl \
        << "Total tests run: " << (success_counter + failed_counter) << std::endl \
        << "Successful: " << success_counter << " | Failed: " << failed_counter << std::endl;

/**
 * Performs an Assertion
 *
 * @param msg the message to print in case of error
 * @param act the actual result
 * @param exp the expected result
 * @param file the filename (for error message)
 * @param line the line in the file (for error message)
 *
 * @return true if act == exp
 */
bool assert_equals(std::string msg, int act, int exp, std::string file,
        int line);

/**
 * Performs an Assertion
 *
 * @param msg the message to print in case of error
 * @param act the actual result
 * @param exp the expected result
 * @param file the filename (for error message)
 * @param line the line in the file (for error message)
 *
 * @return true if act == exp
 */
bool assert_equals(std::string msg, double act, double exp, std::string file,
        int line);

/**
 * Checks if a result was true
 *
 * @param msg the message to print in case of error
 * @param res the result to check
 * @param file the filename (for error message)
 * @param line the line in the file (for error message)
 *
 * @return true if result was true
 */
bool assert_true(std::string msg, bool res, std::string file, int line);

/**
 * Performs an Assertion
 *
 * @param msg  the message to print in case of error
 * @param act  the actual result
 * @param exp  the expected result
 * @param file the filename (for error message)
 * @param line the line in the file (for error message)
 *
 * @return true if !(act != exp)
 */
template<class T>
bool assert_equals(std::string msg, const T& act, const T& exp,
        std::string file, int line);

// template needs to be implemented in header
template<class T>
inline bool assert_equals(std::string msg, const T& act, const T& exp,
        std::string file, int line) {
    if (act != exp) {
        std::cout << RED << "Failed! - " << msg << ": expected <" << exp
                << "> but was <" << act << "> - " << file << ":" << line
                << RESET << std::endl;
        return false;
    }
    return true;
}

#endif /* TEST_BASE_H_ */
