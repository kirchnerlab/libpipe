/*
 * Exception-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct ExceptionTestSuite : vigra::test_suite {
    /** Constructor.
     * The ExceptionTestSuite constructor adds all Exception tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ExceptionTestSuite() : vigra::test_suite("Exception") {
        add(testCase(&ExceptionTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Exception class has tests.
     */
    void fail() {
        failTest("No unit tests for class Exception!");
    }
};


/** The main function that runs the tests for class Exception.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ExceptionTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

