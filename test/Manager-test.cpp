/*
 * Manager-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct ManagerTestSuite : vigra::test_suite {
    /** Constructor.
     * The ManagerTestSuite constructor adds all Manager tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    ManagerTestSuite() : vigra::test_suite("Manager") {
        add(testCase(&ManagerTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Manager class has tests.
     */
    void fail() {
        failTest("No unit tests for class Manager!");
    }
};


/** The main function that runs the tests for class Manager.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    ManagerTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

