/*
 * RequestException-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct RequestExceptionTestSuite : vigra::test_suite {
    /** Constructor.
     * The RequestExceptionTestSuite constructor adds all RequestException tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    RequestExceptionTestSuite() : vigra::test_suite("RequestException") {
        add(testCase(&RequestExceptionTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete RequestException class has tests.
     */
    void fail() {
        failTest("No unit tests for class RequestException!");
    }
};


/** The main function that runs the tests for class RequestException.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    RequestExceptionTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

