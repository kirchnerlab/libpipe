/*
 * Log-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct LogTestSuite : vigra::test_suite {
    /** Constructor.
     * The LogTestSuite constructor adds all Log tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    LogTestSuite() : vigra::test_suite("Log") {
        add(testCase(&LogTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Log class has tests.
     */
    void fail() {
        failTest("No unit tests for class Log!");
    }
};


/** The main function that runs the tests for class Log.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    LogTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

