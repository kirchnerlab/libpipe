/*
 * Algorithm-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct AlgorithmTestSuite : vigra::test_suite {
    /** Constructor.
     * The AlgorithmTestSuite constructor adds all Algorithm tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    AlgorithmTestSuite() : vigra::test_suite("Algorithm") {
        add(testCase(&AlgorithmTestSuite::fail));
    }

    /** Test that is guaranteed to fail.
     * Leave this in until the complete Algorithm class has tests.
     */
    void fail() {
        failTest("No unit tests for class Algorithm!");
    }
};


/** The main function that runs the tests for class Algorithm.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    AlgorithmTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

