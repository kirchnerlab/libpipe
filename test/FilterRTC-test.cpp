/*
 * BasicFilterRTC-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"
#include <libpipe/FilterRTC.hpp>

#include <libpipe/LibpipeFactories.hpp>



/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct FilterRTCTestSuite : vigra::test_suite {
    /** Constructor.
     * The BasicFilterRTCTestSuite constructor adds all BasicFilterRTC tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    FilterRTCTestSuite() : vigra::test_suite("BasicFilterRTC") {
        add(testCase(&FilterRTCTestSuite::test));
    }


    void test() {
        std::string ids="test";

        libpipe_rtc::FilterRTC* bf = libpipe_rtc::FilterFactory::instance().createObject(ids)(ids,ids,ids);
        delete bf;

    }
};


/** The main function that runs the tests for class BasicFilterRTC.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    FilterRTCTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

