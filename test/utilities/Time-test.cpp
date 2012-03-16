/*
 * UTILITIESgetTimeOfDay-test.cpp
 *
 * Copyright (c) 2011 <+author+>
 *
 */

#include <iostream>
#include "vigra/unittest.hxx"
#include <libpipe/utilities/Time.hpp>


/** <+Short description of the test suite+>
 * <+Longer description of the test suite+> 
 */
struct getTimeOfDayTestSuite : vigra::test_suite {
    /** Constructor.
     * The UTILITIESgetTimeOfDayTestSuite constructor adds all UTILITIESgetTimeOfDay tests to
     * the test suite. If you write an additional test, add the test
     * case here.
     */
    getTimeOfDayTestSuite() : vigra::test_suite("UTILITIESgetTimeOfDay") {
        add(testCase(&getTimeOfDayTestSuite::testFreeOperators));
    }

    /** Test free operators
     */
    void testFreeOperators()
    {
        timeval tv1, tv2;
        gettimeofday(&tv1, NULL);
        tv2 = tv1;
        shouldEqual(operator==(tv1, tv2), true);
        shouldEqual(operator==(tv2, tv1), true);
        shouldEqual(operator<=(tv1, tv2), true);
        shouldEqual(operator<=(tv2, tv1), true);
        tv2.tv_sec += 1;
        shouldEqual(operator==(tv1, tv2), false);
        shouldEqual(operator==(tv2, tv1), false);
        shouldEqual(operator<=(tv1, tv2), true);
        shouldEqual(operator<=(tv2, tv1), false);
        libpipe::utilities::set_max(tv2.tv_sec);
        libpipe::utilities::set_max(tv2.tv_usec);
        shouldEqual(operator==(tv1, tv2), false);
        shouldEqual(operator==(tv2, tv1), false);
        shouldEqual(operator<=(tv1, tv2), true);
        shouldEqual(operator<=(tv2, tv1), false);
        libpipe::utilities::set_max(tv1.tv_sec);
        libpipe::utilities::set_max(tv1.tv_usec);
        shouldEqual(operator==(tv1, tv2), true);
        shouldEqual(operator==(tv2, tv1), true);
        shouldEqual(operator<=(tv1, tv2), true);
        shouldEqual(operator<=(tv2, tv1), true);
        libpipe::utilities::set_min(tv2.tv_sec);
        libpipe::utilities::set_min(tv2.tv_usec);
        shouldEqual(operator==(tv1, tv2), false);
        shouldEqual(operator==(tv2, tv1), false);
        shouldEqual(operator<=(tv1, tv2), false);
        shouldEqual(operator<=(tv2, tv1), true);
    }
};


/** The main function that runs the tests for class UTILITIESgetTimeOfDay.
 * Under normal circumstances you need not edit this.
 */
int main()
{
    getTimeOfDayTestSuite test;
    int success = test.run();
    std::cout << test.report() << std::endl;
    return success;
}

