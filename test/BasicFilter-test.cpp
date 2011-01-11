/*
 * BasicFilter-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct BasicFilterTestSuite : vigra::test_suite {
    /** Constructor.
     * The BasicFilterTestSuite constructor adds all BasicFilter tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    BasicFilterTestSuite() : vigra::test_suite("BasicFilter") {
        add(testCase(&BasicFilterTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete BasicFilter class has tests.
     */
    void fail() {
        failTest("No unit tests for class BasicFilter!");
    }
};


/** The main function that runs the tests for class BasicFilter.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    BasicFilterTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

