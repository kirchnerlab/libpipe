/*
 * rtc/LibpipeConfig-test.cpp
 *
 * Copyright (c) 2011 David Sichau
 *                    Marc Kirchner
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"

#include "libpipe/rtc/LibpipeConfig.hpp"


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
        add(testCase(&LibpipeConfigTestSuite::structComparison));
    }



    void structComparison(){
        libpipe::rtc::LibpipePipeStruct s1;
        libpipe::rtc::LibpipePipeStruct s2;

        s1.requestRank = 2;
        s2.requestRank = 3;

        libpipe::rtc::LibpipePipeStructLess compFct;

        shouldEqual(compFct(s1,s2), true);
        shouldEqual(compFct(s2,s1), false);




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

