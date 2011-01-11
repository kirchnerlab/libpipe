/*
 * ModificationTimeManager-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct ModificationTimeManagerTestSuite : vigra::test_suite {
    /** Constructor.
     * The ModificationTimeManagerTestSuite constructor adds all ModificationTimeManager tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ModificationTimeManagerTestSuite() : vigra::test_suite("ModificationTimeManager") {
        add(testCase(&ModificationTimeManagerTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete ModificationTimeManager class has tests.
     */
    void fail() {
        failTest("No unit tests for class ModificationTimeManager!");
    }
};


/** The main function that runs the tests for class ModificationTimeManager.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ModificationTimeManagerTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

