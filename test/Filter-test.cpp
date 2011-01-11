/*
 * Filter-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct FilterTestSuite : vigra::test_suite {
    /** Constructor.
     * The FilterTestSuite constructor adds all Filter tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    FilterTestSuite() : vigra::test_suite("Filter") {
        add(testCase(&FilterTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Filter class has tests.
     */
    void fail() {
        failTest("No unit tests for class Filter!");
    }
};


/** The main function that runs the tests for class Filter.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    FilterTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

