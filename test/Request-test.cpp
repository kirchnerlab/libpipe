/*
 * Request-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct RequestTestSuite : vigra::test_suite {
    /** Constructor.
     * The RequestTestSuite constructor adds all Request tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    RequestTestSuite() : vigra::test_suite("Request") {
        add(testCase(&RequestTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Request class has tests.
     */
    void fail() {
        failTest("No unit tests for class Request!");
    }
};


/** The main function that runs the tests for class Request.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    RequestTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

