/*
 * SimpleManager-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct SimpleManagerTestSuite : vigra::test_suite {
    /** Constructor.
     * The SimpleManagerTestSuite constructor adds all SimpleManager tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    SimpleManagerTestSuite() : vigra::test_suite("SimpleManager") {
        add(testCase(&SimpleManagerTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete SimpleManager class has tests.
     */
    void fail() {
        failTest("No unit tests for class SimpleManager!");
    }
};


/** The main function that runs the tests for class SimpleManager.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    SimpleManagerTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

