/*
 * rtc/LibpipeConfig-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct LibpipeConfigTestSuite : vigra::test_suite {
    /** Constructor.
     * The rtc/LibpipeConfigTestSuite constructor adds all rtc/LibpipeConfig tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    LibpipeConfigTestSuite() : vigra::test_suite("rtc/LibpipeConfig") {
        add(testCase(&LibpipeConfigTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete rtc/LibpipeConfig class has tests.
     */
    void fail() {
        failTest("No unit tests for class rtc/LibpipeConfig!");
    }
};


/** The main function that runs the tests for class rtc/LibpipeConfig.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    LibpipeConfigTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

